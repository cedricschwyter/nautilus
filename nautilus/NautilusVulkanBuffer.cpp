#ifndef NAUTILUS_VULKAN_BUFFER_CPP
#define NAUTILUS_VULKAN_BUFFER_CPP

#include "NautilusVulkanBuffer.hpp"
#include "NautilusAssert.hpp"

NautilusVulkanBuffer::NautilusVulkanBuffer() {
}

NautilusVulkanBuffer::NautilusVulkanBuffer(
    const nautilus::NautilusVulkanCoreHandles&  _core,
    const VkBufferCreateInfo&                   _info, 
    const VkMemoryPropertyFlags&                _prop): m_info(_info), m_core(_core) {
    nautilus::logger::log("Creating buffer...");
    ASSERT_VULKAN(vkCreateBuffer(
        this->m_core.m_logicalDevice,
        &this->m_info,
        this->m_core.m_allocator,
        &this->m_buf));
    nautilus::logger::log("Successfully created buffer");
    VkMemoryRequirements memoryReq;
    vkGetBufferMemoryRequirements(this->m_core.m_logicalDevice, this->m_buf, &memoryReq);
    VkMemoryAllocateInfo memAllocInfo = {};
    memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memAllocInfo.allocationSize = memoryReq.size;
    memAllocInfo.memoryTypeIndex = nautilus::enumerateSuitableVulkanMemoryType(_core, memoryReq.memoryTypeBits, _prop);
    ASSERT_VULKAN(vkAllocateMemory(
        this->m_core.m_logicalDevice,
        &memAllocInfo,
        this->m_core.m_allocator,
        &this->m_mem));
}

NautilusVulkanBuffer::NautilusVulkanBuffer(
    const nautilus::NautilusVulkanCoreHandles&  _core,
    const VkDeviceSize&                         _size, 
    const VkBufferUsageFlags&                   _usage, 
    const VkMemoryPropertyFlags&                _prop) : m_core(_core) {
    VkBufferCreateInfo createInfo = {};
    nautilus::NautilusVulkanQueueFamily fam = nautilus::findSuitableVulkanQueueFamily(this->m_core.m_physicalDevice, this->m_core.m_surface);
    this->m_info = createInfo;
    nautilus::logger::log("Creating buffer...");
    ASSERT_VULKAN(vkCreateBuffer(
        this->m_core.m_logicalDevice,
        &this->m_info,
        this->m_core.m_allocator,
        &this->m_buf));
    nautilus::logger::log("Successfully created buffer");
    VkMemoryRequirements memoryReq;
    vkGetBufferMemoryRequirements(this->m_core.m_logicalDevice, this->m_buf, &memoryReq);
    VkMemoryAllocateInfo memAllocInfo = {};
    memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memAllocInfo.allocationSize = memoryReq.size;
    memAllocInfo.memoryTypeIndex = nautilus::enumerateSuitableVulkanMemoryType(_core, memoryReq.memoryTypeBits, _prop);
    ASSERT_VULKAN(vkAllocateMemory(
        this->m_core.m_logicalDevice,
        &memAllocInfo,
        this->m_core.m_allocator,
        &this->m_mem));
}

NautilusVulkanBuffer::~NautilusVulkanBuffer() {
    vkDestroyBuffer(this->m_core.m_logicalDevice, this->m_buf, this->m_core.m_allocator);
    nautilus::logger::log("Successfully destroyed buffer");
    vkFreeMemory(this->m_core.m_logicalDevice, this->m_mem, this->m_core.m_allocator);
    nautilus::logger::log("Successfully destroyed buffer memory");
}

#endif      // NAUTILUS_VULKAN_BUFFER_CPP