#ifndef NAUTILUS_IMAGE_VULKAN_CPP
#define NAUTILUS_IMAGE_VULKAN_CPP

#include "NautilusImageVulkan.hpp"

NautilusImageVulkan::NautilusImageVulkan() {
}

NautilusImageVulkan::NautilusImageVulkan(nautilus::NautilusCoreHandlesVulkan _core) : m_core(_core) {
}

NautilusImageVulkan::~NautilusImageVulkan() {
    vkDestroyImageView(m_core.m_logicalDevice, m_view, m_core.m_allocator);
    nautilus::logger::log("Successfully destroyed image view");
    vkDestroyImage(m_core.m_logicalDevice, m_img, m_core.m_allocator);
    nautilus::logger::log("Successfully destroyed image");
    vkFreeMemory(m_core.m_logicalDevice, m_mem, m_core.m_allocator);
    nautilus::logger::log("Successfully freed image memory");
}

#endif      // NAUTILUS_IMAGE_VULKAN_CPP