#ifndef NAUTILUS_VULKAN_IMAGE_CPP
#define NAUTILUS_VULKAN_IMAGE_CPP

#include "NautilusVulkanImage.hpp"

NautilusVulkanImage::NautilusVulkanImage() {
}

NautilusVulkanImage::NautilusVulkanImage(nautilus::NautilusVulkanCoreHandles _core) : m_core(_core) {
}

NautilusVulkanImage::~NautilusVulkanImage() {
    vkDestroyImageView(m_core.m_logicalDevice, m_view, m_core.m_allocator);
    nautilus::logger::log("Successfully destroyed image view");
    vkDestroyImage(m_core.m_logicalDevice, m_img, m_core.m_allocator);
    nautilus::logger::log("Successfully destroyed image");
    vkFreeMemory(m_core.m_logicalDevice, m_mem, m_core.m_allocator);
    nautilus::logger::log("Successfully freed image memory");
}

#endif      // NAUTILUS_VULKAN_IMAGE_CPP