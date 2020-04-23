#ifndef NAUTILUS_IMAGE_VULKAN_HPP
#define NAUTILUS_IMAGE_VULKAN_HPP

#include "NautilusCoreHandlesVulkan.hpp"
#include "NautilusLogger.hpp"

#include <vulkan/vulkan.h>

class NautilusImageVulkan {
public:

    /**
     * Default constructor
     */
    NautilusImageVulkan(void);

    /**
     * Constructor with arguments
     */ 
    NautilusImageVulkan(nautilus::NautilusCoreHandlesVulkan _core);

    /**
     * Default destructor
     */
    ~NautilusImageVulkan(void);  

private:

protected:

    nautilus::NautilusCoreHandlesVulkan     m_core;
    VkImage                                 m_img;
    VkDeviceMemory                          m_mem;
    VkFormat                                m_format;
    VkImageView                             m_view;

};

#endif      // NAUTILUS_IMAGE_VULKAN_HPP