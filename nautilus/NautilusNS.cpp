#ifndef NAUTILUS_NS_CPP
#define NAUTILUS_NS_CPP

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "NautilusNS.hpp"

namespace nautilus {

    const std::string                   globalApplicationName                   = nautilus::defaults::CONTEXT_NAME;
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
    bool                                vulkanInstanceCreated                   = false;
    VkAllocationCallbacks*              vulkanAllocator                         = nullptr;
    bool                                enableVulkanValidationLayers            = false;
    const std::vector< const char* >    vulkanValidationLayers                  = {
            "VK_LAYER_KHRONOS_validation",
    };
    VkDebugUtilsMessengerEXT            vulkanValidationLayerDebugMessenger     = VK_NULL_HANDLE;
    const std::vector< const char* >    vulkanRequiredExtensions                = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    VkSampleCountFlagBits               maxVulkanMSAASampleCount                = VK_SAMPLE_COUNT_1_BIT;


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

    nautilus::NautilusStatus freeSTBI(unsigned char* _pixels) {
        stbi_image_free(_pixels);
        return NAUTILUS_STATUS_OK;
    }

    nautilus::NautilusStatus createVulkanInstance() {
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
            exts += "\n\t" + extName;
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

    nautilus::NautilusStatus createVulkanDebugMessenger() {
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

    nautilus::NautilusStatus destroyVulkanDebugUtilsMessenger(
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

    NautilusVulkanQueueFamily findSuitableVulkanQueueFamily(VkPhysicalDevice _device, VkSurfaceKHR _surface) {
        NautilusVulkanQueueFamily family;
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, nullptr);
        std::vector< VkQueueFamilyProperties > queueFamily(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, queueFamily.data());
        int i = 0;
        for(const auto& qF : queueFamily) {
            if(qF.queueCount > 0 && (qF.queueFlags & VK_QUEUE_GRAPHICS_BIT))   // Does the queue family have at least one queue and does it support graphics-operations?
                family.m_graphicsFamilyIndex = i;
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(
                _device,
                i, 
                _surface,
                &presentSupport);
            if(qF.queueCount > 0 && presentSupport)            // Also a presentation queue family is needed to actually display to the surface
                family.m_presentationFamilyIndex = i;
            if(qF.queueCount > 0 && (qF.queueFlags & VK_QUEUE_TRANSFER_BIT) 
                && !(qF.queueFlags & VK_QUEUE_GRAPHICS_BIT))    // Transfer queue for memory operations
                family.m_transferFamilyIndex = i;
            if(family.isComplete()) 
                break;
            i++;
        }
        return family;
    }

    NautilusVulkanQueueFamily findSuitableVulkanQueueFamily(const NautilusVulkanCoreHandles& _handles) {
        return nautilus::findSuitableVulkanQueueFamily(_handles.m_physicalDevice, _handles.m_surface);
    }

    uint32_t enumerateSuitableVulkanMemoryType(
        const NautilusVulkanCoreHandles&       _handles, 
        const uint32_t&                        _typeFilter, 
        const VkMemoryPropertyFlags&           _memoryPropertyFlags) {
        VkPhysicalDeviceMemoryProperties memProp;
        vkGetPhysicalDeviceMemoryProperties(_handles.m_physicalDevice, &memProp);
        for (uint32_t i = 0; i < memProp.memoryTypeCount; i++) 
            // Does the memory type have all of the necessary properties?
            if (_typeFilter & (1 << i) && (memProp.memoryTypes[i].propertyFlags & _memoryPropertyFlags) == _memoryPropertyFlags)       // Some bitwise-operation magic to find appropriate bit-indices
                return i;
        logger::log("Failed to find suitable memory type!", NAUTILUS_STATUS_FATAL);
        return NAUTILUS_STATUS_FATAL;
    }

    VkCommandBuffer startVulkanCommandBuffer(const nautilus::NautilusVulkanQueueType& _queue) {
        return VkCommandBuffer();
    }

    NautilusStatus endVulkanCommandBuffer(const VkCommandBuffer& _cmdBuf) {
        return NAUTILUS_STATUS_OK;
    }

    template< typename _T >
    std::size_t hashField(std::size_t* _hash, const _T& _field) {
        std::hash< _T > hashFunc;
        *_hash ^= hashFunc(_field) + 0x9e3779b9 + (*_hash << 6) + (*_hash >> 2);
        return *_hash;
    }
    
    const std::vector< char > loadFile(const std::string& _path) {
        nautilus::logger::log("Loading file at '" + _path + "'");
        std::ifstream file(_path, std::ios::ate | std::ios::binary);        // Start reading at end of file --> determine the buffer size needed
        if(!file.is_open()) 
            nautilus::logger::log("Failed to load file at '" + _path + "'");
        size_t bufferSize = (size_t)file.tellg();        // Find read position and thus necessary buffer size
        std::vector< char > buffer(bufferSize);
        file.seekg(0);        // Translate back to the beginning of the file
        file.read(buffer.data(), bufferSize);
        file.close();
        return buffer;
    }

}

#endif      // NAUTILUS_NS_CPP