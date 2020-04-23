#ifndef NAUTILUS_SWAPCHAIN_DETAILS_VULKAN_HPP
#define NAUTILUS_SWAPCHAIN_DETAILS_VULKAN_HPP

#include <vulkan/vulkan.h>

#include <vector>

namespace nautilus {

    struct NautilusSwapchainDetailsVulkan {
        VkSurfaceCapabilitiesKHR            m_surfaceCapabilities;
        std::vector< VkSurfaceFormatKHR >   m_supportedFormats;
        std::vector< VkPresentModeKHR >     m_presentationModes;
    };

}

#endif  // NAUTILUS_SWAPCHAIN_DETAILS_VULKAN_HPP
