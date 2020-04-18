#ifndef NAUTILUS_VERTEX_HPP
#define NAUTILUS_VERTEX_HPP

#include "NautilusNS.hpp"

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include <array>
#include <functional>

class NautilusVertex {
public:

    alignas(16) glm::vec3 m_pos;
    alignas(16) glm::vec3 m_nor;
    alignas(16) glm::vec2 m_tex;
    alignas(16) glm::vec3 m_tan;
    alignas(16) glm::vec3 m_bit;

    /**
     * Returns the binding description for Vulkan
     * @return Returns a VkVertexInputBindingDescription structure
     */ 
    static VkVertexInputBindingDescription getBindingDescription(void);

    /**
     * Returns the attribute descriptions for Vulkan
     * @return Returns an array with attribute descriptions
     */ 
    static std::array< VkVertexInputAttributeDescription, 5 > getAttributeDescriptions(void);

    /**
     * Comparison operator overload
     * @param _other The other instance
     * @return Returns true if the vertices are the same
     */ 
    bool operator==(const NautilusVertex& _other) const;
    
    friend struct std::hash< NautilusVertex >;

};

/**
 * Custom hash function
 */
namespace std {
    template< typename _T >
    struct hash;
    template< >
    struct hash< NautilusVertex > {
        std::size_t operator()(const NautilusVertex& _inst) const noexcept;
    };
}

#endif      // NAUTILUS_VERTEX_HPP