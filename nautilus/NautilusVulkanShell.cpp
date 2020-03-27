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
    this->createLogicalDevice();
    this->createSwapchain();
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
    std::set< std::string > extensions(nautilus::vulkanRequiredExtensions.begin(), nautilus::vulkanRequiredExtensions.end());
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
    for(const auto& qF : queueFamily) {
        if(qF.queueCount > 0 && (qF.queueFlags & VK_QUEUE_GRAPHICS_BIT))   // Does the queue family have at least one queue and does it support graphics-operations?
            family.graphicsFamilyIndex = i;
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(
            _device,
            i, 
            this->m_surface,
            &presentSupport);
        if(qF.queueCount > 0 && presentSupport)            // Also a presentation queue family is needed to actually display to the surface
            family.presentationFamilyIndex = i;
        if(qF.queueCount > 0 && (qF.queueFlags & VK_QUEUE_TRANSFER_BIT) 
            && !(qF.queueFlags & VK_QUEUE_GRAPHICS_BIT))    // Transfer queue for memory operations
            family.transferFamilyIndex = i;
        if(family.isComplete()) 
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

NautilusStatus NautilusVulkanShell::createLogicalDevice() {
    nautilus::logger::log("Creating logical device...");
    NautilusVulkanQueueFamily family = findSuitableQueueFamily(this->m_physicalDevice);
    std::vector< VkDeviceQueueCreateInfo > deviceQueueCreateInfos;
    std::set< uint32_t > uniqueQueueFamilies = { family.graphicsFamilyIndex.value(), family.presentationFamilyIndex.value(), family.transferFamilyIndex.value() };
    float queuePriority = 1.0f;
    for(uint32_t qF : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo deviceQueueCreateInfo          = {};
        deviceQueueCreateInfo.sType                            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        deviceQueueCreateInfo.queueFamilyIndex                 = qF;
        deviceQueueCreateInfo.queueCount                       = 1;
        deviceQueueCreateInfo.pQueuePriorities                 = &queuePriority;
        deviceQueueCreateInfos.push_back(deviceQueueCreateInfo);
    }
    VkPhysicalDeviceFeatures physicalDeviceFeatures            = {};
    physicalDeviceFeatures.samplerAnisotropy                   = VK_TRUE;
    physicalDeviceFeatures.fillModeNonSolid                    = VK_TRUE;
    VkDeviceCreateInfo deviceCreateInfo                        = {};
    deviceCreateInfo.sType                                     = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount                      = static_cast< uint32_t >(deviceQueueCreateInfos.size());
    deviceCreateInfo.pQueueCreateInfos                         = deviceQueueCreateInfos.data();
    deviceCreateInfo.enabledExtensionCount                     = static_cast< uint32_t >(nautilus::vulkanRequiredExtensions.size());
    deviceCreateInfo.ppEnabledExtensionNames                   = nautilus::vulkanRequiredExtensions.data();
    deviceCreateInfo.pEnabledFeatures                          = &physicalDeviceFeatures;
    if(nautilus::enableVulkanValidationLayers) {
        deviceCreateInfo.enabledLayerCount                     = static_cast< uint32_t >(nautilus::vulkanValidationLayers.size());
        deviceCreateInfo.ppEnabledLayerNames                   = nautilus::vulkanValidationLayers.data();
    } else
        deviceCreateInfo.enabledLayerCount                     = 0;
    ASSERT_VULKAN(vkCreateDevice(
        this->m_physicalDevice, 
        &deviceCreateInfo, 
        nautilus::vulkanAllocator, 
        &this->m_logicalDevice));
    nautilus::logger::log("Successfully created logical device");
    nautilus::logger::log("Retrieving queue handle for graphics queue...");
    vkGetDeviceQueue(
        this->m_logicalDevice,
        family.graphicsFamilyIndex.value(),
        0,
        &this->m_graphicsQueue);
    nautilus::logger::log("Successfully retrieved queue handle for graphics queue");
    nautilus::logger::log("Retrieving queue handle for presentation queue...");
    vkGetDeviceQueue(
        this->m_logicalDevice,
        family.presentationFamilyIndex.value(),
        0,
        &this->m_presentQueue);
    nautilus::logger::log("Successfully retrieved queue handle for presentation queue");
    nautilus::logger::log("Retrieving queue handle for transfer queue...");
    vkGetDeviceQueue(
        this->m_logicalDevice,
        family.transferFamilyIndex.value(),
        0,
        &this->m_transferQueue);
    nautilus::logger::log("Successfully retrieved queue handle for transfer queue");
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusVulkanShell::createSwapchain() {
    nautilus::logger::log("Creating swapchain...");
    NautilusVulkanSwapchainDetails  details             = this->querySwapchainDetails(this->m_physicalDevice);
    VkSurfaceFormatKHR              surfaceFormat       = this->evaluateBestSwapchainSurfaceFormat(details.supportedFormats);
    VkPresentModeKHR                presentMode         = this->evaluateBestSwapchainSurfacePresentMode(details.presentationModes);
    VkExtent2D                      extent              = this->evaluateSwapchainExtent(details.surfaceCapabilities);
    this->m_swapchainImageFormat                        = surfaceFormat.format;
    this->m_swapchainImageExtent                        = extent;
    uint32_t                        swapchainImageCount = details.surfaceCapabilities.minImageCount + 1;
    if(details.surfaceCapabilities.maxImageCount > 0 && swapchainImageCount > details.surfaceCapabilities.maxImageCount)
        swapchainImageCount                             = details.surfaceCapabilities.maxImageCount;
    VkSwapchainCreateInfoKHR        swapchainCreateInfo = {};
    swapchainCreateInfo.sType                           = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainCreateInfo.surface                         = this->m_surface;
    swapchainCreateInfo.minImageCount                   = swapchainImageCount;
    swapchainCreateInfo.imageFormat                     = surfaceFormat.format;
    swapchainCreateInfo.imageColorSpace                 = surfaceFormat.colorSpace;
    swapchainCreateInfo.imageExtent                     = extent;
    swapchainCreateInfo.imageArrayLayers                = 1;                                          // Amount of layers in an image, always 1, unless doing stereoscopic stuff
    swapchainCreateInfo.imageUsage                      = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;        // Render directly to swapchain
    NautilusVulkanQueueFamily family                    = this->findSuitableQueueFamily(this->m_physicalDevice);
    uint32_t queueFamilyIndices[]                       = { family.graphicsFamilyIndex.value(), family.presentationFamilyIndex.value() };
    if(family.graphicsFamilyIndex != family.presentationFamilyIndex) {           // If presentation queue and graphics queue are in the same queue family, exclusive ownership is not necessary
        swapchainCreateInfo.imageSharingMode            = VK_SHARING_MODE_CONCURRENT;
        swapchainCreateInfo.queueFamilyIndexCount       = 2;
        swapchainCreateInfo.pQueueFamilyIndices         = queueFamilyIndices;
    }
    else  // else it is
        swapchainCreateInfo.imageSharingMode            = VK_SHARING_MODE_EXCLUSIVE;
    swapchainCreateInfo.preTransform                    = details.surfaceCapabilities.currentTransform;        // Specify current image transform as no transform is necessary
    swapchainCreateInfo.compositeAlpha                  = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;                   // Window should not be blended with other windows behind it, no thanks
    swapchainCreateInfo.clipped                         = true;                                                // Do not render pixels that are outside the clip space as this is just performance loss
    swapchainCreateInfo.presentMode                     = presentMode;
    swapchainCreateInfo.oldSwapchain                    = VK_NULL_HANDLE;
    ASSERT_VULKAN(vkCreateSwapchainKHR(
        this->m_logicalDevice,
        &swapchainCreateInfo,
        nautilus::vulkanAllocator,
        &this->m_swapchain));
    nautilus::logger::log("Successfully created swapchain");
    nautilus::logger::log("Retrieving the handles for the swapchain images...");
    vkGetSwapchainImagesKHR(
        this->m_logicalDevice, 
        this->m_swapchain,
        &swapchainImageCount,
        nullptr);
    this->m_swapchainImages.resize(swapchainImageCount);
    vkGetSwapchainImagesKHR(
        this->m_logicalDevice,
        this->m_swapchain,
        &swapchainImageCount,
        this->m_swapchainImages.data());
    nautilus::logger::log("Successfully retrieved the handles for the swapchain images");
    return NAUTILUS_STATUS_OK;
}

VkSurfaceFormatKHR NautilusVulkanShell::evaluateBestSwapchainSurfaceFormat(const std::vector< VkSurfaceFormatKHR >& _availableFormats) {
    if(_availableFormats.size() == 1 && _availableFormats[0].format == VK_FORMAT_UNDEFINED)     // If Vulkan only returns one entry and its format is set to VK_FORMAT_UNDEFINED it means that Vulkan has no preferred format so we can choose freely
        return { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
    for(const auto& format : _availableFormats)
        if(format.format == VK_FORMAT_B8G8R8A8_UNORM && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)  
            return format;
    return _availableFormats[0];        // If there are no better choices, just return the first one in the array, usually it is good enough
}

VkPresentModeKHR NautilusVulkanShell::evaluateBestSwapchainSurfacePresentMode(const std::vector< VkPresentModeKHR >& _availablePresentModes) {
    for(const auto& presMode : _availablePresentModes)
        if(presMode == VK_PRESENT_MODE_MAILBOX_KHR) // VK_PRESENT_MODE_MAILBOX_KHR MAY cause tearing issues in borderless window or fullscreen mode
            return presMode;
    return VK_PRESENT_MODE_FIFO_KHR;        // If no better mode is available, return VK_PRESENT_MODE_FIFO_KHR as its implied to be supported if the GPU support Vulkan
}

VkExtent2D NautilusVulkanShell::evaluateSwapchainExtent(const VkSurfaceCapabilitiesKHR& _capabilities) {
    if(_capabilities.currentExtent.width != std::numeric_limits< uint32_t >::max())
        return _capabilities.currentExtent;
    else {
        int width, height;
        glfwGetFramebufferSize(this->m_window, &width, &height);
        VkExtent2D preferredExtent = {
            static_cast< uint32_t >(width),
            static_cast< uint32_t >(height)
        };
        preferredExtent.width             = std::clamp(preferredExtent.width, _capabilities.minImageExtent.width, _capabilities.maxImageExtent.width);
        preferredExtent.height            = std::clamp(preferredExtent.height, _capabilities.minImageExtent.height, _capabilities.maxImageExtent.height);
        return preferredExtent;
    }
}

#endif      // NAUTILUS_VULKAN_SHELL_CPP