#ifndef NAUTILUS_CORE_CPP
#define NAUTILUS_CORE_CPP

#include "NautilusCore.hpp"
#include "NautilusUtil.hpp"

namespace nautilus {

    NautilusStatus NautilusCore::attach(NautilusShell* _shell) {
        return get().attachI(_shell);
    }

    NautilusStatus NautilusCore::detach(NautilusShell* _shell) {
        return get().detachI(_shell);
    }

    NautilusStatus NautilusCore::loop() {
        return get().loopI();
    }

    bool NautilusCore::exit() {
        return get().exitI();
    }

    NautilusStatus NautilusCore::terminate() {
        return get().terminateI();
    }

    NautilusStatus NautilusCore::setEnableVulkanValidationLayers() {
        return get().setEnableVulkanValidationLayersI();
    }

    NautilusStatus NautilusCore::createVulkanInstance() {
        return get().createVulkanInstanceI();
    }

    bool NautilusCore::vulkanValidationLayersSupported() {
        return get().vulkanValidationLayersSupportedI();
    }

    std::vector< const char* > NautilusCore::queryRequiredVulkanExtensions() {
        return get().queryRequiredVulkanExtensionsI();
    }

    NautilusStatus NautilusCore::createVulkanDebugMessenger() {
        return get().createVulkanDebugMessengerI();
    }

    VkAllocationCallbacks* NautilusCore::vulkanAllocator() {
        return get().vulkanAllocatorI();
    }

    VkInstance NautilusCore::vulkanInstance() {
        return get().vulkanInstanceI();
    }

    VkAllocationCallbacks* NautilusCore::vulkanAllocatorI() {
        return m_vulkanAllocator;
    }

    VkInstance NautilusCore::vulkanInstanceI() {
        return m_vulkanInstance;
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL NautilusCore::vulkanValidationLayerDebugMessageCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT           _messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT                  _messageType,
        const VkDebugUtilsMessengerCallbackDataEXT*      _pCallbackData,
        void*                                            _pUserData) {
        return get().vulkanValidationLayerDebugMessageCallbackI(
            _messageSeverity,
            _messageType,
            _pCallbackData,
            _pUserData);
    }

    VkResult NautilusCore::createVulkanDebugUtilsMessenger(
        VkInstance                                      _instance,
        const VkDebugUtilsMessengerCreateInfoEXT*       _pCreateInfo,
        const VkAllocationCallbacks*                    _pAllocator,
        VkDebugUtilsMessengerEXT*                       _pDebugMessenger) {
        return get().createVulkanDebugUtilsMessengerI(
            _instance, 
            _pCreateInfo, 
            _pAllocator, 
            _pDebugMessenger);
    }

    NautilusStatus NautilusCore::destroyVulkanDebugUtilsMessenger(
        VkInstance                          _instance,
        VkDebugUtilsMessengerEXT            _debugMessenger,
        const VkAllocationCallbacks*        _pAllocator) {
        return get().destroyVulkanDebugUtilsMessengerI(_instance, _debugMessenger, _pAllocator);
    }

    NautilusQueueFamilyVulkan NautilusCore::findSuitableVulkanQueueFamily(VkPhysicalDevice _device, VkSurfaceKHR _surface) {
        return get().findSuitableVulkanQueueFamilyI(_device, _surface);
    }

    NautilusQueueFamilyVulkan NautilusCore::findSuitableVulkanQueueFamily(const NautilusCoreHandlesVulkan& _handles) {
        return get().findSuitableVulkanQueueFamilyI(_handles);
    }

    uint32_t NautilusCore::enumerateSuitableVulkanMemoryType(
        const NautilusCoreHandlesVulkan&       _handles, 
        const uint32_t&                        _typeFilter, 
        const VkMemoryPropertyFlags&           _memoryPropertyFlags) {
        return get().enumerateSuitableVulkanMemoryTypeI(_handles, _typeFilter, _memoryPropertyFlags);
    }

    bool NautilusCore::enableVulkanValidationLayers() {
        return get().enableVulkanValidationLayersI();
    }

    VkDebugUtilsMessengerEXT NautilusCore::vulkanValidationLayerDebugMessenger() {
        return get().vulkanValidationLayerDebugMessengerI();
    }

    std::vector< const char* > const& NautilusCore::vulkanValidationLayers() {
        return get().vulkanValidationLayersI();
    }

    std::vector< const char* > const& NautilusCore::vulkanRequiredExtensions() {
        return get().vulkanRequiredExtensionsI();
    }

    NautilusCore::NautilusCore() {
    }

    NautilusCore& NautilusCore::get() {
        static NautilusCore s_instance;
        return s_instance;
    }

    NautilusStatus NautilusCore::attachI(NautilusShell* _shell) {
        static int32_t id = 0;
        std::unique_lock< std::mutex > idLock(_shell->m_idLock);
        _shell->m_id = id;
        idLock.unlock();
        id++;
        m_shellCount++;
        std::unique_lock< std::mutex > shellLock(m_shellsLock);
        m_shells.push_back(_shell);
        shellLock.unlock();
        if(!m_running) {
            m_running = true;
            m_t0 = std::async(std::launch::async, NautilusCore::loop);
        }
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusCore::detachI(NautilusShell* _shell) {
        m_shells.erase(m_shells.begin() 
            + util::getIndexOfElement(m_shells, _shell).second);
        std::scoped_lock< std::mutex > shellCountLock(m_shellCountLock);
        m_shellCount--;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusCore::loopI() {
        glfwInit();
        while(!exit()) {
            logger::meta();
        }
        glfwTerminate();
        logger::terminate();
        return NAUTILUS_STATUS_OK;
    }

    bool NautilusCore::exitI() {
        std::scoped_lock< std::mutex > exitLock(m_shellCountLock);
        return m_shellCount == 0;
    }

    NautilusStatus NautilusCore::terminateI() {
        m_t0.wait();
        std::unique_lock< std::mutex > exitMutex(m_exitLock);
        m_exit = true;
        exitMutex.unlock();
        std::unique_lock< std::mutex > shellLock(m_shellsLock);
        for(auto shell : m_shells)
            delete shell;
        shellLock.unlock();
        std::scoped_lock< std::mutex > lock(m_threadpoolLock);
        for(auto& t : m_threadpool) t.wait();
        return NAUTILUS_STATUS_OK;
    }

    bool NautilusCore::enableVulkanValidationLayersI() {
        return m_enableVulkanValidationLayers;
    }

    VkDebugUtilsMessengerEXT NautilusCore::vulkanValidationLayerDebugMessengerI() {
        return m_vulkanValidationLayerDebugMessenger;
    }

    std::vector< const char* > const& NautilusCore::vulkanValidationLayersI() {
        return m_vulkanValidationLayers;
    }

    std::vector< const char* > const& NautilusCore::vulkanRequiredExtensionsI() {
        return m_vulkanRequiredExtensions;
    }

    NautilusStatus NautilusCore::setEnableVulkanValidationLayersI() {
        m_enableVulkanValidationLayers = true;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusCore::createVulkanInstanceI() {
        if(m_vulkanInstanceCreated) return NAUTILUS_STATUS_OK;
        logger::log("Requesting Vulkan validation layers...");
        if(m_enableVulkanValidationLayers&& vulkanValidationLayersSupportedI())
            logger::log("Successfully activated Vulkan validation layers");
        else
            logger::log("Vulkan validation layers are not available", NAUTILUS_STATUS_FATAL);
        auto extensions = queryRequiredVulkanExtensionsI();
        VkApplicationInfo applicationInfo                  = {};
        applicationInfo.sType                              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pApplicationName                   = defaults::CONTEXT_NAME.c_str();
        applicationInfo.applicationVersion                 = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.pEngineName                        = defaults::CONTEXT_NAME.c_str();
        applicationInfo.engineVersion                      = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.apiVersion                         = VK_API_VERSION_1_0;
        VkInstanceCreateInfo instanceCreateInfo            = {};
        instanceCreateInfo.sType                           = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo                = &applicationInfo;
        instanceCreateInfo.enabledExtensionCount           = static_cast< uint32_t >(extensions.size());
        instanceCreateInfo.ppEnabledExtensionNames         = extensions.data();   
        if(m_enableVulkanValidationLayers) {   
            instanceCreateInfo.enabledLayerCount           = static_cast< uint32_t >(m_vulkanValidationLayers.size());
            instanceCreateInfo.ppEnabledLayerNames         = m_vulkanValidationLayers.data();
        } else  
            instanceCreateInfo.enabledLayerCount           = 0;
        logger::log("Creating VkInstance...");
        VkResult result = vkCreateInstance(&instanceCreateInfo, m_vulkanAllocator, &m_vulkanInstance);
        ASSERT_VULKAN(result);
        logger::log("Successfully created VkInstance");
        m_vulkanInstanceCreated = true;
        return NAUTILUS_STATUS_OK;
    }

    bool NautilusCore::vulkanValidationLayersSupportedI() {
        uint32_t validationLayerCount;
        vkEnumerateInstanceLayerProperties(&validationLayerCount, nullptr);
        std::vector< VkLayerProperties > availableValidationLayers(validationLayerCount);
        vkEnumerateInstanceLayerProperties(&validationLayerCount, availableValidationLayers.data());
        // Check if all layers in vulkanValidationLayers exist in availableValidationLayers
        for(const char* layer : m_vulkanValidationLayers) {
            bool found = false;
            for(const auto& layerProp : availableValidationLayers)
                if(strcmp(layer, layerProp.layerName) == 0) {
                    found = true;
                    break;
                }
            if(!found) 
                return false;
        }
        return true;
    }

    std::vector< const char* > NautilusCore::queryRequiredVulkanExtensionsI() {
        logger::log("Querying available extensions...");
        uint32_t extCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
        std::vector< VkExtensionProperties > availableExtensions(extCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extCount, availableExtensions.data());
        std::string exts = "Available extensions:";
        for(const auto& ext : availableExtensions) {
            std::string extName = ext.extensionName;
            exts += "\n\t" + extName;
        }
        logger::log(exts.c_str());
        uint32_t glfwExtCount = 0;
        const char** glfwExt;
        logger::log("Querying GLFW-extensions...");
        glfwExt = glfwGetRequiredInstanceExtensions(&glfwExtCount);
        logger::log("Successfully enabled required GLFW-extensions");
        std::vector< const char* > extensions(glfwExt, glfwExt + glfwExtCount);
        if(m_enableVulkanValidationLayers)
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        return extensions;
    }

    NautilusStatus NautilusCore::createVulkanDebugMessengerI() {
        if(!m_enableVulkanValidationLayers) return NAUTILUS_STATUS_OK;
        logger::log("Creating Vulkan debug utils messenger...");
        VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo        = {};
        debugUtilsMessengerCreateInfo.sType                                     = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugUtilsMessengerCreateInfo.messageSeverity                           = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
                                                                                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                                                                                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugUtilsMessengerCreateInfo.messageType                               = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                                                                                | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                                                                                | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugUtilsMessengerCreateInfo.pfnUserCallback                           = NautilusCore::vulkanValidationLayerDebugMessageCallback;
        debugUtilsMessengerCreateInfo.pUserData                                 = nullptr;
        VkResult result = createVulkanDebugUtilsMessengerI(
            m_vulkanInstance,
            &debugUtilsMessengerCreateInfo,
            m_vulkanAllocator,
            &m_vulkanValidationLayerDebugMessenger);
        ASSERT_VULKAN(result);
        logger::log("Successfully created Vulkan debug utils messenger");
        return NAUTILUS_STATUS_OK;
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL NautilusCore::vulkanValidationLayerDebugMessageCallbackI(
        VkDebugUtilsMessageSeverityFlagBitsEXT           _messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT                  _messageType,
        const VkDebugUtilsMessengerCallbackDataEXT*      _pCallbackData,
        void*                                            _pUserData) {
        std::string header = "Validation Layer:    ";
        std::string message(_pCallbackData->pMessage);
        if(_messageSeverity > VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
            logger::log(header + message, NAUTILUS_STATUS_FATAL);
        else
            logger::log(header + message);
        return VK_FALSE;
    }

    VkResult NautilusCore::createVulkanDebugUtilsMessengerI(
        VkInstance                                      _instance,
        const VkDebugUtilsMessengerCreateInfoEXT*       _pCreateInfo,
        const VkAllocationCallbacks*                    _pAllocator,
        VkDebugUtilsMessengerEXT*                       _pDebugMessenger) {
        logger::log("Gathering proc-address for 'vkCreateDebugUtilsMessengerEXT'");
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

    NautilusStatus NautilusCore::destroyVulkanDebugUtilsMessengerI(
        VkInstance                          _instance,
        VkDebugUtilsMessengerEXT            _debugMessenger,
        const VkAllocationCallbacks*        _pAllocator) {
        logger::log("Gathering proc-address for 'vkDestroyDebugUtilsMessengerEXT'");
        auto destroyDebugMessenger = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT");
        if(destroyDebugMessenger != nullptr) {
            destroyDebugMessenger(_instance, _debugMessenger, _pAllocator);
            return NAUTILUS_STATUS_OK;
        } else
            return NAUTILUS_STATUS_FATAL;
    }

    NautilusQueueFamilyVulkan NautilusCore::findSuitableVulkanQueueFamilyI(VkPhysicalDevice _device, VkSurfaceKHR _surface) {
        NautilusQueueFamilyVulkan family;
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

    NautilusQueueFamilyVulkan NautilusCore::findSuitableVulkanQueueFamilyI(const NautilusCoreHandlesVulkan& _handles) {
        return findSuitableVulkanQueueFamilyI(_handles.m_physicalDevice, _handles.m_surface);
    }

    uint32_t NautilusCore::enumerateSuitableVulkanMemoryTypeI(
        const NautilusCoreHandlesVulkan&       _handles, 
        const uint32_t&                        _typeFilter, 
        const VkMemoryPropertyFlags&           _memoryPropertyFlags) {
        VkPhysicalDeviceMemoryProperties memProp;
        vkGetPhysicalDeviceMemoryProperties(_handles.m_physicalDevice, &memProp);
        for(uint32_t i = 0; i < memProp.memoryTypeCount; i++) 
            // Does the memory type have all of the necessary properties?
            if(_typeFilter & (1 << i) && (memProp.memoryTypes[i].propertyFlags & _memoryPropertyFlags) == _memoryPropertyFlags)       // Some bitwise-operation magic to find appropriate bit-indices
                return i;
        logger::log("Failed to find suitable memory type!", NAUTILUS_STATUS_FATAL);
        return NAUTILUS_STATUS_FATAL;
    }

    NautilusCore::~NautilusCore() {
    }

}

#endif      // NAUTILUS_CORE_CPP