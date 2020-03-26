#ifndef NAUTILUS_VULKAN_SHELL_CPP
#define NAUTILUS_VULKAN_SHELL_CPP

#include "NautilusVulkanShell.hpp"

void NautilusVulkanShell::onAttach() {
}

void NautilusVulkanShell::onRender() {
}

NautilusStatus NautilusVulkanShell::setDefaultWindowHints() {
    this->m_title = "Standard OpenGL Example with nautilus by D3PSI";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusVulkanShell::initAPI() {
    if(this->m_initializedAPI) return NAUTILUS_STATUS_OK;
    nautilus::logger::log("Initializing Vulkan...");
    nautilus::createVulkanInstance();
    nautilus::createVulkanDebugMessenger();
    this->createSurfaceGLFW();
    this->selectBestPhysicalDevice();
    glfwShowWindow(this->m_window);
    glfwFocusWindow(this->m_window);
    this->m_initializedAPI = true;
    nautilus::logger::log("Successfully initialized Vulkan");
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusVulkanShell::createSurfaceGLFW() {
    nautilus::logger::log("Creating Vulkan surface...");
    ASSERT_VULKAN(glfwCreateWindowSurface(
        nautilus::vulkanInstance, 
        this->m_window, 
        nautilus::vulkanAllocator, 
        &this->m_surface));
    nautilus::logger::log("Successfully created Vulkan surface");
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusVulkanShell::selectBestPhysicalDevice() {
    nautilus::logger::log("Enumerating GPUs...");
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(nautilus::vulkanInstance, &physicalDeviceCount, nullptr);
    if(physicalDeviceCount == 0) {
        nautilus::logger::log("Failed to find a suitable GPU", NAUTILUS_STATUS_FATAL);
        return NAUTILUS_STATUS_FATAL;
    }
    std::vector< VkPhysicalDevice > physicalDevices(physicalDeviceCount);
    vkEnumeratePhysicalDevices(nautilus::vulkanInstance, &physicalDeviceCount, physicalDevices.data());
    std::multimap< int, VkPhysicalDevice > possibleGPUs;
    for(const auto& physicalDev : physicalDevices) {
        this->printPhysicalDevicePropertiesAndFeatures(physicalDev);
        int rating = evaluateDeviceSuitabilityScore(physicalDev);
        possibleGPUs.insert(std::make_pair(rating, physicalDev));
    }
    if(possibleGPUs.rbegin()->first > 0) {        // Is the first possibility even suitable?
        nautilus::logger::log("Suitable GPU found: ");
        this->printPhysicalDevicePropertiesAndFeatures(possibleGPUs.rbegin()->second);
        this->m_physicalDevice = possibleGPUs.rbegin()->second;
        nautilus::maxVulkanMSAASampleCount = this->enumerateMaximumMultisamplingSampleCount();
        nautilus::logger::log("Enumerated maximum multisampling count: " + nautilus::maxVulkanMSAASampleCount);
        return NAUTILUS_STATUS_OK;
    } else {
        nautilus::logger::log("Failed to find a suitable GPU that supports Vulkan", NAUTILUS_STATUS_FATAL);
        return NAUTILUS_STATUS_FATAL;
    }

}

uint32_t NautilusVulkanShell::evaluateDeviceSuitabilityScore(VkPhysicalDevice _device) {
    NautilusVulkanQueueFamily       family                = this->findSuitableQueueFamily(_device);
    NautilusVulkanSwapchainDetails  swapchainDetails      = this->querySwapchainDetails(_device);
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(_device, &physicalDeviceProperties);
    VkPhysicalDeviceFeatures physicalDeviceFeatures;
    vkGetPhysicalDeviceFeatures(_device, &physicalDeviceFeatures);
    int score = 0;
    if(physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        score += 1000;
    if(!family.isComplete() 
        || !this->checkDeviceSwapchainExtensionSupport(_device) 
        || swapchainDetails.supportedFormats.empty() 
        || swapchainDetails.presentationModes.empty()
        || !physicalDeviceFeatures.samplerAnisotropy)       // absolutely necessary features needed to run application on that GPU
        return 0;
    return score;
}

NautilusStatus NautilusVulkanShell::printPhysicalDevicePropertiesAndFeatures(VkPhysicalDevice _device) {
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(_device, &physicalDeviceProperties);
    VkPhysicalDeviceFeatures physicalDeviceFeatures;
    vkGetPhysicalDeviceFeatures(_device, &physicalDeviceFeatures);
    // TODO: Print info
    std::string info = std::string("GPU information:    ") + physicalDeviceProperties.deviceName;
    nautilus::logger::log(info);
    return NAUTILUS_STATUS_OK;
}

bool NautilusVulkanShell::checkDeviceSwapchainExtensionSupport(VkPhysicalDevice _device) {
    nautilus::logger::log("Checking, whether the device supports the necessary extensions...");
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(
        _device,
        nullptr,
        &extensionCount,
        nullptr);
    std::vector< VkExtensionProperties > availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(
        _device,
        nullptr,
        &extensionCount, 
        availableExtensions.data());
    // Check whether all required extensions are amongst the available ones
    std::set< std::string > extensions(nautilus::requiredExtensions.begin(), nautilus::requiredExtensions.end());
    for(const auto& extension : availableExtensions)
        extensions.erase(extension.extensionName);
    if(extensions.empty())
        nautilus::logger::log("Device supports necessary extensions");
    else
        nautilus::logger::log("Device does not support necessary extensions", NAUTILUS_STATUS_FATAL);
    return extensions.empty();
}

VkSampleCountFlagBits NautilusVulkanShell::enumerateMaximumMultisamplingSampleCount() {
    VkPhysicalDeviceProperties physicalDeviceProps;
    vkGetPhysicalDeviceProperties(this->m_physicalDevice, &physicalDeviceProps);
    VkSampleCountFlags counts = std::min(physicalDeviceProps.limits.framebufferColorSampleCounts, physicalDeviceProps.limits.framebufferDepthSampleCounts);
    if(counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
    if(counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
    if(counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
    if(counts & VK_SAMPLE_COUNT_8_BIT)  { return VK_SAMPLE_COUNT_8_BIT;  }
    if(counts & VK_SAMPLE_COUNT_4_BIT)  { return VK_SAMPLE_COUNT_4_BIT;  }
    if(counts & VK_SAMPLE_COUNT_2_BIT)  { return VK_SAMPLE_COUNT_2_BIT;  }
    return VK_SAMPLE_COUNT_1_BIT;
}

NautilusVulkanQueueFamily NautilusVulkanShell::findSuitableQueueFamily(VkPhysicalDevice _device) {
    NautilusVulkanQueueFamily family;
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, nullptr);
    std::vector< VkQueueFamilyProperties > queueFamily(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(_device, &queueFamilyCount, queueFamily.data());
    int i = 0;
    for (const auto& qF : queueFamily) {
        if (qF.queueCount > 0 && (qF.queueFlags & VK_QUEUE_GRAPHICS_BIT))   // Does the queue family have at least one queue and does it support graphics-operations?
            family.graphicsFamilyIndex = i;
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(
            _device,
            i, 
            this->m_surface,
            &presentSupport);
        if (qF.queueCount > 0 && presentSupport)            // Also a presentation queue family is needed to actually display to the surface
            family.presentationFamilyIndex = i;
        if (qF.queueCount > 0 && (qF.queueFlags & VK_QUEUE_TRANSFER_BIT) 
            && !(qF.queueFlags & VK_QUEUE_GRAPHICS_BIT))    // Transfer queue for memory operations
            family.transferFamilyIndex = i;
        if (family.isComplete()) 
            break;
        i++;
    }
    return family;
}

NautilusVulkanSwapchainDetails NautilusVulkanShell::querySwapchainDetails(VkPhysicalDevice _device) {
    nautilus::logger::log("Gathering swapchain details...");
    NautilusVulkanSwapchainDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_device, this->m_surface, &details.surfaceCapabilities);
    uint32_t numFormats;
    vkGetPhysicalDeviceSurfaceFormatsKHR(
        _device, 
        this->m_surface, 
        &numFormats, 
        nullptr);
    if(numFormats != 0) {
        details.supportedFormats.resize(numFormats);
        vkGetPhysicalDeviceSurfaceFormatsKHR(
            _device,
            this->m_surface,
            &numFormats,
            details.supportedFormats.data());
    }
    uint32_t numPresentModes;
    vkGetPhysicalDeviceSurfacePresentModesKHR(
        _device,
        this->m_surface,
        &numPresentModes,
        nullptr);
    if(numPresentModes != 0) {     
        details.presentationModes.resize(numPresentModes);
        vkGetPhysicalDeviceSurfacePresentModesKHR(
            _device,
            this->m_surface,
            &numPresentModes,
            details.presentationModes.data());
    }
    nautilus::logger::log("Successfully gathered swapchain details");
    return details;
}

#endif      // NAUTILUS_VULKAN_SHELL_CPP