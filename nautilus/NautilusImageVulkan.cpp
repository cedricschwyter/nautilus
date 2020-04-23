#ifndef NAUTILUS_IMAGE_VULKAN_CPP
#define NAUTILUS_IMAGE_VULKAN_CPP

#include "NautilusImageVulkan.hpp"

namespace nautilus {
        
    NautilusImageVulkan::NautilusImageVulkan() {
    }

    NautilusImageVulkan::NautilusImageVulkan(NautilusCoreHandlesVulkan _core) : m_core(_core) {
    }

    NautilusImageVulkan::~NautilusImageVulkan() {
        vkDestroyImageView(m_core.m_logicalDevice, m_view, m_core.m_allocator);
        logger::log("Successfully destroyed image view");
        vkDestroyImage(m_core.m_logicalDevice, m_img, m_core.m_allocator);
        logger::log("Successfully destroyed image");
        vkFreeMemory(m_core.m_logicalDevice, m_mem, m_core.m_allocator);
        logger::log("Successfully freed image memory");
    }

}

#endif      // NAUTILUS_IMAGE_VULKAN_CPP