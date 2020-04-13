#ifndef NAUTILUS_VULKAN_IMAGE_CPP
#define NAUTILUS_VULKAN_IMAGE_CPP

#include "NautilusVulkanImage.hpp"

NautilusVulkanImage::NautilusVulkanImage() {
}

NautilusVulkanImage::NautilusVulkanImage(nautilus::NautilusVulkanCoreHandles _core) : m_core(_core) {
}

NautilusVulkanImage::~NautilusVulkanImage() {
    vkDestroyImageView(this->m_core.m_logicalDevice, this->m_view, this->m_core.m_allocator);
    nautilus::logger::log("Successfully destroyed image view");
    vkDestroyImage(this->m_core.m_logicalDevice, this->m_img, this->m_core.m_allocator);
    nautilus::logger::log("Successfully destroyed image");
    vkFreeMemory(this->m_core.m_logicalDevice, this->m_mem, this->m_core.m_allocator);
    nautilus::logger::log("Successfully freed image memory");
}

#endif      // NAUTILUS_VULKAN_IMAGE_CPP