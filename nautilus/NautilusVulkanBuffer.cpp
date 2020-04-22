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
        m_core.m_logicalDevice,
        &m_info,
        m_core.m_allocator,
        &m_buf));
    nautilus::logger::log("Successfully created buffer");
    VkMemoryRequirements memoryReq;
    vkGetBufferMemoryRequirements(m_core.m_logicalDevice, m_buf, &memoryReq);
    VkMemoryAllocateInfo memAllocInfo = {};
    memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memAllocInfo.allocationSize = memoryReq.size;
    memAllocInfo.memoryTypeIndex = nautilus::enumerateSuitableVulkanMemoryType(_core, memoryReq.memoryTypeBits, _prop);
    ASSERT_VULKAN(vkAllocateMemory(
        m_core.m_logicalDevice,
        &memAllocInfo,
        m_core.m_allocator,
        &m_mem));
    bind();
}

NautilusVulkanBuffer::NautilusVulkanBuffer(
    const nautilus::NautilusVulkanCoreHandles&  _core,
    const VkDeviceSize&                         _size, 
    const VkBufferUsageFlags&                   _usage, 
    const VkMemoryPropertyFlags&                _prop) : m_core(_core) {
    VkBufferCreateInfo createInfo = {};
    nautilus::NautilusVulkanQueueFamily fam = nautilus::findSuitableVulkanQueueFamily(m_core.m_physicalDevice, m_core.m_surface);
    m_info = createInfo;
    nautilus::logger::log("Creating buffer...");
    ASSERT_VULKAN(vkCreateBuffer(
        m_core.m_logicalDevice,
        &m_info,
        m_core.m_allocator,
        &m_buf));
    nautilus::logger::log("Successfully created buffer");
    VkMemoryRequirements memoryReq;
    vkGetBufferMemoryRequirements(m_core.m_logicalDevice, m_buf, &memoryReq);
    VkMemoryAllocateInfo memAllocInfo = {};
    memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memAllocInfo.allocationSize = memoryReq.size;
    memAllocInfo.memoryTypeIndex = nautilus::enumerateSuitableVulkanMemoryType(_core, memoryReq.memoryTypeBits, _prop);
    ASSERT_VULKAN(vkAllocateMemory(
        m_core.m_logicalDevice,
        &memAllocInfo,
        m_core.m_allocator,
        &m_mem));
    bind();
}

NautilusVulkanBuffer::NautilusVulkanBuffer(const NautilusVulkanBuffer& _other) {
    VkBufferCopy copy = {};
    copy.size = _other.m_info.size;
    VkCommandBuffer cmdBuf = nautilus::startVulkanCommandBuffer(nautilus::NAUTILUS_VULKAN_QUEUE_TRANSFER);
    vkCmdCopyBuffer(
        cmdBuf, 
        _other.m_buf, 
        m_buf, 
        1, 
        &copy);
    nautilus::endVulkanCommandBuffer(cmdBuf);
}

NautilusVulkanBuffer& NautilusVulkanBuffer::operator=(const NautilusVulkanBuffer& _other) {
    VkBufferCopy copy = {};
    copy.size = _other.m_info.size;
    VkCommandBuffer cmdBuf = nautilus::startVulkanCommandBuffer(nautilus::NAUTILUS_VULKAN_QUEUE_TRANSFER);
    vkCmdCopyBuffer(
        cmdBuf, 
        _other.m_buf, 
        m_buf, 
        1, 
        &copy);
    nautilus::endVulkanCommandBuffer(cmdBuf);
    return *this;
}

NautilusVulkanBuffer::~NautilusVulkanBuffer() {
    vkDestroyBuffer(m_core.m_logicalDevice, m_buf, m_core.m_allocator);
    nautilus::logger::log("Successfully destroyed buffer");
    vkFreeMemory(m_core.m_logicalDevice, m_mem, m_core.m_allocator);
    nautilus::logger::log("Successfully destroyed buffer memory");
}

nautilus::NautilusStatus NautilusVulkanBuffer::bind() {
    ASSERT_VULKAN(vkBindBufferMemory(
        m_core.m_logicalDevice,
        m_buf,
        m_mem,
        static_cast< uint64_t >(0)));
    return nautilus::NAUTILUS_STATUS_OK;
}

template< typename _T >
nautilus::NautilusStatus NautilusVulkanBuffer::fill(const _T& _data, const bool _staging) {
    return nautilus::NAUTILUS_STATUS_OK;
}

template< typename _T >
nautilus::NautilusStatus NautilusVulkanBuffer::fill(_T&& _data, const bool _staging) {
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusVulkanBuffer::fill(const void* _data, const bool _staging) {
    if(!_staging) {
        void* data;
        vkMapMemory(
            m_core.m_logicalDevice,
            m_mem,
            0,
            m_info.size,
            0,
            &data
            );
        memcpy(data, _data, static_cast< size_t >(m_info.size));
        vkUnmapMemory(m_core.m_logicalDevice, m_mem);
    } else {
        nautilus::NautilusVulkanQueueFamily family  = nautilus::findSuitableVulkanQueueFamily(m_core.m_physicalDevice, m_core.m_surface);
        std::vector< uint32_t > indices             = { family.m_transferFamilyIndex.value() };
        VkBufferCreateInfo bufferCreateInfo         = {};
        bufferCreateInfo.sType                      = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferCreateInfo.size                       = m_info.size;
        bufferCreateInfo.usage                      = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        bufferCreateInfo.sharingMode                = VK_SHARING_MODE_EXCLUSIVE;
        bufferCreateInfo.pQueueFamilyIndices        = indices.data();
        bufferCreateInfo.queueFamilyIndexCount      = static_cast< uint32_t >(indices.size());
        NautilusVulkanBuffer stagingBuffer          = NautilusVulkanBuffer(
                                                            m_core, 
                                                            bufferCreateInfo, 
                                                            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT 
                                                            | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        stagingBuffer.fill(_data);
        *this = stagingBuffer;
    }
    return nautilus::NAUTILUS_STATUS_OK;
}

#endif      // NAUTILUS_VULKAN_BUFFER_CPP