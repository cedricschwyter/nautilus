#ifndef NAUTILUS_VULKAN_BUFFER_HPP
#define NAUTILUS_VULKAN_BUFFER_HPP

#include "NautilusLogger.hpp"
#include "NautilusNS.hpp"
#include "NautilusVulkanQueueFamily.hpp"
#include "NautilusVulkanCoreHandles.hpp"
#include "NautilusVulkanQueueFamily.hpp"
#include "NautilusVulkanQueueType.hpp"
#include "NautilusNS.hpp"

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
     * Copy constructor
     * @param _other The other instance to copy values from
     */
    NautilusVulkanBuffer(const NautilusVulkanBuffer& _other); 

    /**
     * Assignment operator
     * @param _other The other instance to copy values from
     * @return Returns a reference to a NautilusVulkanBuffer instance
     */ 
    NautilusVulkanBuffer& operator=(const NautilusVulkanBuffer& _other);

    /**
     * Binds a buffer
     * @return Returns a nautilus::NautilusStatus status code
     */ 
    nautilus::NautilusStatus bind(void);

    /**
     * Fills a buffer
     * @param _data The data to fill the buffer with
     * @param _staging Use a staging buffer
     * @return Returns a nautilus::NautilusStatus status code
     */ 
    template< typename T >
    nautilus::NautilusStatus fill(const T& _data, const bool _staging = false);
    template< typename T >
    nautilus::NautilusStatus fill(T&& _data, const bool _staging = false);
    nautilus::NautilusStatus fill(const void* _data, const bool _staging = false);

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