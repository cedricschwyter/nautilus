#ifndef NAUTILUS_CORE_HANDLES_VULKAN_HPP
#define NAUTILUS_CORE_HANDLES_VULKAN_HPP

#include <vulkan/vulkan.h>

namespace nautilus {

    struct NautilusCoreHandlesVulkan {
        VkInstance                  m_instance;
        VkDevice                    m_logicalDevice;
        VkPhysicalDevice            m_physicalDevice;
        VkSurfaceKHR                m_surface;
        VkAllocationCallbacks*      m_allocator;
        VkSwapchainKHR              m_swapchain;      
        VkFormat                    m_swapchainImageFormat;
        VkExtent2D                  m_swapchainImageExtent;
    };

}

#endif      // NAUTILUS_CORE_HANDLES_VULKAN_HPP