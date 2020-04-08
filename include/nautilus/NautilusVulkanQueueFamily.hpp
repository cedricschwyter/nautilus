#ifndef NAUTILUS_VULKAN_QUEUE_FAMILY_HPP
#define NAUTILUS_VULKAN_QUEUE_FAMILY_HPP

#include <optional>

namespace nautilus {

    struct NautilusVulkanQueueFamily {
        std::optional< uint32_t > m_graphicsFamilyIndex;
        std::optional< uint32_t > m_presentationFamilyIndex;
        std::optional< uint32_t > m_transferFamilyIndex;

        /**
         * Checks whether a queue family index has been found
         * @return Returns true if an index exists for every required queue 
         */
        bool isComplete(void) {
            return m_graphicsFamilyIndex.has_value() && m_presentationFamilyIndex.has_value() && m_transferFamilyIndex.has_value();
        }
    };

}

#endif  // NAUTILUS_VULKAN_QUEUE_FAMILY_HPP
