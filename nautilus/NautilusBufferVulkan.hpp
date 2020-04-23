#ifndef NAUTILUS_BUFFER_VULKAN_HPP
#define NAUTILUS_BUFFER_VULKAN_HPP

#include "NautilusLogger.hpp"
#include "NautilusUtil.hpp"
#include "NautilusQueueFamilyVulkan.hpp"
#include "NautilusCoreHandlesVulkan.hpp"
#include "NautilusQueueFamilyVulkan.hpp"
#include "NautilusQueueTypeVulkan.hpp"

#include <vulkan/vulkan.h>

namespace nautilus {

    class NautilusBufferVulkan {
    public:

        /**
         * Default constructor
         */
        NautilusBufferVulkan(void); 

        /**
         * Constructor with arguments
         * @param _core The core nautilus handles
         * @param _info The VkBufferCreateInfo structure for Vulkan
         * @param _prop The required memory properties for the buffer
         */
        NautilusBufferVulkan(
            const NautilusCoreHandlesVulkan&  _core,
            const VkBufferCreateInfo&                   _info, 
            const VkMemoryPropertyFlags&                _prop); 

        /**
         * Constructor with arguments
         * @param _core The core nautilus handles
         * @param _size The buffer size
         * @param _usage How the buffer will be used
         * @param _prop The required memory properties for the buffer
         */ 
        NautilusBufferVulkan(
            const NautilusCoreHandlesVulkan&  _core,
            const VkDeviceSize&                         _size, 
            const VkBufferUsageFlags&                   _usage, 
            const VkMemoryPropertyFlags&                _prop);

        /**
         * Copy constructor
         * @param _other The other instance to copy values from
         */
        NautilusBufferVulkan(const NautilusBufferVulkan& _other); 

        /**
         * Assignment operator
         * @param _other The other instance to copy values from
         * @return Returns a reference to a NautilusVulkanBuffer instance
         */ 
        NautilusBufferVulkan& operator=(const NautilusBufferVulkan& _other);

        /**
         * Binds a buffer
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus bind(void);

        /**
         * Fills a buffer
         * @param _data The data to fill the buffer with
         * @param _staging Use a staging buffer
         * @return Returns a NautilusStatus status code
         */ 
        template< typename _T >
        NautilusStatus fill(const _T& _data, const bool _staging = false);
        template< typename _T >
        NautilusStatus fill(_T&& _data, const bool _staging = false);
        NautilusStatus fill(const void* _data, const bool _staging = false);

        /**
         * Default destructor
         */ 
        ~NautilusBufferVulkan(void);

    private:

    protected:

        NautilusCoreHandlesVulkan     m_core;
        VkBuffer                                m_buf       = VK_NULL_HANDLE;
        VkDeviceMemory                          m_mem       = VK_NULL_HANDLE;
        VkBufferCreateInfo                      m_info      = {};

    };

}

#endif      // NAUTILUS_BUFFER_VULKAN_HPP