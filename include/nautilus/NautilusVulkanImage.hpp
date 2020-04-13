#ifndef NAUTILUS_VULKAN_IMAGE_HPP
#define NAUTILUS_VULKAN_IMAGE_HPP

#include "NautilusVulkanCoreHandles.hpp"
#include "NautilusLogger.hpp"

#include <vulkan/vulkan.h>

class NautilusVulkanImage {
public:

    /**
     * Default constructor
     */
    NautilusVulkanImage(void);

    /**
     * Constructor with arguments
     */ 
    NautilusVulkanImage(nautilus::NautilusVulkanCoreHandles _core);

    /**
     * Default destructor
     */
    ~NautilusVulkanImage(void);  

private:

protected:

    nautilus::NautilusVulkanCoreHandles     m_core;
    VkImage                                 m_img;
    VkDeviceMemory                          m_mem;
    VkFormat                                m_format;
    VkImageView                             m_view;

};

#endif      // NAUTILUS_VULKAN_IMAGE_HPP