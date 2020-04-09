#ifndef NAUTILUS_VULKAN_BUFFER_HPP
#define NAUTILUS_VULKAN_BUFFER_HPP

#include "NautilusLogger.hpp"
#include "NautilusNS.hpp"
#include "NautilusVulkanQueueFamily.hpp"
#include "NautilusVulkanCoreHandles.hpp"

#include <vulkan/vulkan.h>

class NautilusVulkanBuffer {
public:

    /**
     * Default constructor
     */
    NautilusVulkanBuffer(void); 

    /**
     * Constructor with arguments
     * @param _core The core nautilus handles
     * @param _info The VkBufferCreateInfo structure for Vulkan
     * @param _prop The required memory properties for the buffer
     */
    NautilusVulkanBuffer(
        const nautilus::NautilusVulkanCoreHandles&  _core,
        const VkBufferCreateInfo&                   _info, 
        const VkMemoryPropertyFlags&                _prop); 

    /**
     * Constructor with arguments
     * @param _core The core nautilus handles
     * @param _size The buffer size
     * @param _usage How the buffer will be used
     * @param _prop The required memory properties for the buffer
     */ 
    NautilusVulkanBuffer(
        const nautilus::NautilusVulkanCoreHandles&  _core,
        const VkDeviceSize&                         _size, 
        const VkBufferUsageFlags&                   _usage, 
        const VkMemoryPropertyFlags&                _prop);

    /**
     * Default destructor
     */ 
    ~NautilusVulkanBuffer(void);

private:

protected:

    nautilus::NautilusVulkanCoreHandles     m_core;
    VkBuffer                                m_buf       = VK_NULL_HANDLE;
    VkDeviceMemory                          m_mem       = VK_NULL_HANDLE;
    VkBufferCreateInfo                      m_info      = {};

};

#endif      // NAUTILUS_VULKAN_BUFFER_HPP