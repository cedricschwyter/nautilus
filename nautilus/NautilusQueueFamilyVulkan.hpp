#ifndef NAUTILUS_QUEUE_FAMILY_VULKAN_HPP
#define NAUTILUS_QUEUE_FAMILY_VULKAN_HPP

#include <optional>

namespace nautilus {

    struct NautilusQueueFamilyVulkan {
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

#endif  // NAUTILUS_QUEUE_FAMILY_VULKAN_HPP
