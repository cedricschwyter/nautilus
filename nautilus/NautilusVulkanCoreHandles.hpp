#ifndef NAUTILUS_VULKAN_CORE_HANDLES_HPP
#define NAUTILUS_VULKAN_CORE_HANDLES_HPP

#include <vulkan/vulkan.h>

namespace nautilus {

    struct NautilusVulkanCoreHandles {
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

#endif      // NAUTILUS_VULKAN_CORE_HANDLES_HPP