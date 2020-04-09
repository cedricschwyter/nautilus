#ifndef NAUTILUS_VULKAN_SWAPCHAIN_DETAILS_HPP
#define NAUTILUS_VULKAN_SWAPCHAIN_DETAILS_HPP

#include <vulkan/vulkan.h>

#include <vector>

namespace nautilus {

    struct NautilusVulkanSwapchainDetails {
        VkSurfaceCapabilitiesKHR            m_surfaceCapabilities;
        std::vector< VkSurfaceFormatKHR >   m_supportedFormats;
        std::vector< VkPresentModeKHR >     m_presentationModes;
    };

}

#endif  // NAUTILUS_VULKAN_SWAPCHAIN_DETAILS_HPP
