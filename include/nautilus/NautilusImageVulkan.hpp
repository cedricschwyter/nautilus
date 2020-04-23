#ifndef NAUTILUS_IMAGE_VULKAN_HPP
#define NAUTILUS_IMAGE_VULKAN_HPP

#include "NautilusCoreHandlesVulkan.hpp"
#include "NautilusLogger.hpp"

#include <vulkan/vulkan.h>

namespace nautilus {

    class NautilusImageVulkan {
    public:

        /**
         * Default constructor
         */
        NautilusImageVulkan(void);

        /**
         * Constructor with arguments
         */ 
        NautilusImageVulkan(NautilusCoreHandlesVulkan _core);

        /**
         * Default destructor
         */
        ~NautilusImageVulkan(void);  

    private:

    protected:

        NautilusCoreHandlesVulkan     m_core;
        VkImage                                 m_img;
        VkDeviceMemory                          m_mem;
        VkFormat                                m_format;
        VkImageView                             m_view;

    };

}

#endif      // NAUTILUS_IMAGE_VULKAN_HPP