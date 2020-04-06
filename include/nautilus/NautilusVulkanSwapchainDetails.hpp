#ifndef NAUTILUS_VULKAN_SWAPCHAIN_DETAILS_HPP
#define NAUTILUS_VULKAN_SWAPCHAIN_DETAILS_HPP

#include <vulkan/vulkan.h>

#include <vector>

namespace nautilus {

    struct NautilusVulkanSwapchainDetails {
        VkSurfaceCapabilitiesKHR            surfaceCapabilities;
        std::vector< VkSurfaceFormatKHR >   supportedFormats;
        std::vector< VkPresentModeKHR >     presentationModes;
    };

}

#endif  // NAUTILUS_VULKAN_SWAPCHAIN_DETAILS_HPP
