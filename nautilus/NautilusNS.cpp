#ifndef NAUTILUS_NS_CPP
#define NAUTILUS_NS_CPP

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "NautilusNS.hpp"

namespace nautilus {

    std::string                         globalApplicationName                   = "Nautilus by D3PSI";
    bool                                exit                                    = false;
    std::mutex                          exitLock;
    bool                                running                                 = false;
    std::mutex                          runningLock;
    std::vector< NautilusShell* >       shells;
    std::mutex                          shellsLock;
    std::vector< std::thread* >         threadpool;
    std::mutex                          threadpoolLock;
    uint32_t                            shellCount                              = 0;
    std::mutex                          shellCountLock;
    VkInstance                          vulkanInstance                          = VK_NULL_HANDLE;
    VkAllocationCallbacks*              vulkanAllocator                         = nullptr;
    bool                                vulkanInstanceCreated                   = false;
    bool                                enableVulkanValidationLayers            = false;
    const std::vector< const char* >    vulkanValidationLayers                  = {
            "VK_LAYER_LUNARG_standard_validation"
    };
    VkDebugUtilsMessengerEXT            vulkanValidationLayerDebugMessenger     = VK_NULL_HANDLE;

    unsigned char* loadSTBI(
        std::string _path, 
        int*        _x, 
        int*        _y, 
        int*        _comp, 
        int         _req_comp) {
        return reinterpret_cast<unsigned char*>(stbi_load(
                    _path.c_str(),
                    _x,
                    _y,
                    _comp,
                    _req_comp));
    }

    NautilusStatus freeSTBI(unsigned char* _pixels) {
        stbi_image_free(_pixels);
        return NAUTILUS_STATUS_OK;
    }

    template< typename T >
    std::pair< bool, int32_t > getIndexOfElement(const std::vector< T >& _vec, const T& _element) {
        std::pair< bool, int32_t > result;
        auto it = std::find(_vec.begin(), _vec.end(), _element);
        if (it != _vec.end()) {
            result.second = std::distance(_vec.begin(), it);
            result.first = true;
        }
        else {
            result.first = false;
            result.second = -1;
        }
        return result;
    }

    template< typename T >
    std::pair< bool, int32_t > getIndexOfElement(const std::vector< T* >& _vec, const T* _element) {
        std::pair< bool, int32_t > result;
        auto it = std::find(_vec.begin(), _vec.end(), _element);
        if (it != _vec.end()) {
            result.second = std::distance(_vec.begin(), it);
            result.first = true;
        }
        else {
            result.first = false;
            result.second = -1;
        }
        return result;
    }

    NautilusStatus createVulkanInstance() {
        if(nautilus::vulkanInstanceCreated) return NAUTILUS_STATUS_OK;
        nautilus::logger::log("Requesting Vulkan validation layers...");
        if(nautilus::enableVulkanValidationLayers && nautilus::vulkanValidationLayersSupported())
            nautilus::logger::log("Successfully activated Vulkan validation layers");
        else
            nautilus::logger::log("Vulkan validation layers are not available", NAUTILUS_STATUS_FATAL);
        auto extensions = nautilus::queryRequiredVulkanExtensions();
        VkApplicationInfo applicationInfo                  = {};
        applicationInfo.sType                              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pApplicationName                   = nautilus::globalApplicationName.c_str();
        applicationInfo.applicationVersion                 = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.pEngineName                        = nautilus::globalApplicationName.c_str();
        applicationInfo.engineVersion                      = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.apiVersion                         = VK_API_VERSION_1_0;
        VkInstanceCreateInfo instanceCreateInfo            = {};
        instanceCreateInfo.sType                           = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo                = &applicationInfo;
        instanceCreateInfo.enabledExtensionCount           = static_cast< uint32_t >(extensions.size());
        instanceCreateInfo.ppEnabledExtensionNames         = extensions.data();   
        if(nautilus::enableVulkanValidationLayers) {   
            instanceCreateInfo.enabledLayerCount           = static_cast< uint32_t >(nautilus::vulkanValidationLayers.size());
            instanceCreateInfo.ppEnabledLayerNames         = nautilus::vulkanValidationLayers.data();
        }
        else  
            instanceCreateInfo.enabledLayerCount           = 0;
        nautilus::logger::log("Creating VkInstance...");
        VkResult result = vkCreateInstance(&instanceCreateInfo, nautilus::vulkanAllocator, &nautilus::vulkanInstance);
        ASSERT_VULKAN(result);
        nautilus::logger::log("Successfully created VkInstance");
        nautilus::vulkanInstanceCreated = true;
        return NAUTILUS_STATUS_OK;
    }

    bool vulkanValidationLayersSupported() {
        uint32_t validationLayerCount;
        vkEnumerateInstanceLayerProperties(&validationLayerCount, nullptr);
        std::vector< VkLayerProperties > availableValidationLayers(validationLayerCount);
        vkEnumerateInstanceLayerProperties(&validationLayerCount, availableValidationLayers.data());
        // Check if all layers in vulkanValidationLayers exist in availableValidationLayers
        for (const char* layer : nautilus::vulkanValidationLayers) {
            bool found = false;
            for (const auto& layerProp : availableValidationLayers)
                if (strcmp(layer, layerProp.layerName) == 0) {
                    found = true;
                    break;
                }
            if (!found) 
                return false;
        }
        return true;
    }

    std::vector< const char* > queryRequiredVulkanExtensions() {
        nautilus::logger::log("Querying available extensions...");
        uint32_t extCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
        std::vector< VkExtensionProperties > availableExtensions(extCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extCount, availableExtensions.data());
        std::string exts = "Available extensions:";
        for (const auto& ext : availableExtensions) {
            std::string extName = ext.extensionName;
            exts += "\n\t\t\t\t" + extName;
        }
        nautilus::logger::log(exts.c_str());
        uint32_t glfwExtCount = 0;
        const char** glfwExt;
        nautilus::logger::log("Querying GLFW-extensions...");
        glfwExt = glfwGetRequiredInstanceExtensions(&glfwExtCount);
        nautilus::logger::log("Successfully enabled required GLFW-extensions");
        std::vector< const char* > extensions(glfwExt, glfwExt + glfwExtCount);
        if (nautilus::enableVulkanValidationLayers)
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        return extensions;
    }

    NautilusStatus createVulkanDebugMessenger() {
        if(!nautilus::enableVulkanValidationLayers) return NAUTILUS_STATUS_OK;
        nautilus::logger::log("Creating Vulkan debug utils messenger...");
        VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo        = {};
        debugUtilsMessengerCreateInfo.sType                                     = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugUtilsMessengerCreateInfo.messageSeverity                           = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
                                                                                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                                                                                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugUtilsMessengerCreateInfo.messageType                               = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                                                                                | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                                                                                | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugUtilsMessengerCreateInfo.pfnUserCallback                           = nautilus::vulkanValidationLayerDebugMessageCallback;
        debugUtilsMessengerCreateInfo.pUserData                                 = nullptr;
        VkResult result = nautilus::createVulkanDebugUtilsMessenger(
            nautilus::vulkanInstance,
            &debugUtilsMessengerCreateInfo,
            nautilus::vulkanAllocator,
            &nautilus::vulkanValidationLayerDebugMessenger);
        ASSERT_VULKAN(result);
        nautilus::logger::log("Successfully created Vulkan debug utils messenger");
        return NAUTILUS_STATUS_OK;
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL vulkanValidationLayerDebugMessageCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT           _messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT                  _messageType,
        const VkDebugUtilsMessengerCallbackDataEXT*      _pCallbackData,
        void*                                            _pUserData) {
        std::string header = "Validation Layer:    ";
        std::string message(_pCallbackData->pMessage);
        if(_messageSeverity > VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
            nautilus::logger::log(header + message, NAUTILUS_STATUS_FATAL);
        else
            nautilus::logger::log(header + message);
        return VK_FALSE;
    }

    VkResult createVulkanDebugUtilsMessenger(
        VkInstance                                      _instance,
        const VkDebugUtilsMessengerCreateInfoEXT*       _pCreateInfo,
        const VkAllocationCallbacks*                    _pAllocator,
        VkDebugUtilsMessengerEXT*                       _pDebugMessenger) {
        nautilus::logger::log("Gathering proc-address for 'vkCreateDebugUtilsMessengerEXT'");
        // Get debug-messenger-creation-proc-address from Vulkan
        auto createDebugMessenger = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
        if(createDebugMessenger != nullptr)
            return createDebugMessenger(
                _instance,
                _pCreateInfo,
                _pAllocator,
                _pDebugMessenger);
        else
            return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    NautilusStatus destroyVulkanDebugUtilsMessenger(
        VkInstance                          _instance,
        VkDebugUtilsMessengerEXT            _debugMessenger,
        const VkAllocationCallbacks*        _pAllocator) {
        nautilus::logger::log("Gathering proc-address for 'vkDestroyDebugUtilsMessengerEXT'");
        auto destroyDebugMessenger = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT");
        if(destroyDebugMessenger != nullptr) {
            destroyDebugMessenger(_instance, _debugMessenger, _pAllocator);
            return NAUTILUS_STATUS_OK;
        } else
            return NAUTILUS_STATUS_FATAL;
    }

}

#endif      // NAUTILUS_NS_CPP