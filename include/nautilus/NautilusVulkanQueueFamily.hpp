#ifndef NAUTILUS_VULKAN_QUEUE_FAMILY_HPP
#define NAUTILUS_VULKAN_QUEUE_FAMILY_HPP

#include <optional>

struct NautilusVulkanQueueFamily {
    std::optional< uint32_t > graphicsFamilyIndex;
    std::optional< uint32_t > presentationFamilyIndex;
    std::optional< uint32_t > transferFamilyIndex;

    /**
     * Checks whether a queue family index has been found
     * @return Returns true if an index exists for every required queue 
     */
    bool isComplete(void) {
        return graphicsFamilyIndex.has_value() && presentationFamilyIndex.has_value() && transferFamilyIndex.has_value();
    }
};
#endif  // NAUTILUS_VULKAN_QUEUE_FAMILY_HPP
