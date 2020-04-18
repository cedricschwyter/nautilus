#ifndef NAUTILUS_VULKAN_CPP
#define NAUTILUS_VULKAN_CPP

#include "NautilusVertex.hpp"

VkVertexInputBindingDescription NautilusVertex::getBindingDescription() {
    VkVertexInputBindingDescription vertexInputBindingDescription                       = {};
    vertexInputBindingDescription.binding                                               = 0;
    vertexInputBindingDescription.stride                                                = sizeof(NautilusVertex);
    vertexInputBindingDescription.inputRate                                             = VK_VERTEX_INPUT_RATE_VERTEX;
    return vertexInputBindingDescription;
}
 
std::array< VkVertexInputAttributeDescription, 5 > NautilusVertex::getAttributeDescriptions(void) {
    std::array< VkVertexInputAttributeDescription, 5 > vertexInputAttributeDescriptions = {};
    vertexInputAttributeDescriptions[0].binding                                         = 0;
    vertexInputAttributeDescriptions[0].location                                        = 0;
    vertexInputAttributeDescriptions[0].format                                          = VK_FORMAT_R32G32B32_SFLOAT;            
    vertexInputAttributeDescriptions[0].offset                                          = offsetof(NautilusVertex, m_pos);
    vertexInputAttributeDescriptions[1].binding                                         = 0;
    vertexInputAttributeDescriptions[1].location                                        = 1;
    vertexInputAttributeDescriptions[1].format                                          = VK_FORMAT_R32G32B32_SFLOAT;
    vertexInputAttributeDescriptions[1].offset                                          = offsetof(NautilusVertex, m_nor);
    vertexInputAttributeDescriptions[2].binding                                         = 0;
    vertexInputAttributeDescriptions[2].location                                        = 2;
    vertexInputAttributeDescriptions[2].format                                          = VK_FORMAT_R32G32_SFLOAT;
    vertexInputAttributeDescriptions[2].offset                                          = offsetof(NautilusVertex, m_tex);
    vertexInputAttributeDescriptions[3].binding                                         = 0;
    vertexInputAttributeDescriptions[3].location                                        = 3;
    vertexInputAttributeDescriptions[3].format                                          = VK_FORMAT_R32G32B32_SFLOAT;
    vertexInputAttributeDescriptions[3].offset                                          = offsetof(NautilusVertex, m_tan);
    vertexInputAttributeDescriptions[4].binding                                         = 0;
    vertexInputAttributeDescriptions[4].location                                        = 4;
    vertexInputAttributeDescriptions[4].format                                          = VK_FORMAT_R32G32B32_SFLOAT;
    vertexInputAttributeDescriptions[4].offset                                          = offsetof(NautilusVertex, m_bit);
    return vertexInputAttributeDescriptions;
}

bool NautilusVertex::operator==(const NautilusVertex& _other) const {
    return this->m_pos == _other.m_pos 
        && this->m_nor == _other.m_nor
        && this->m_tex == _other.m_tex 
        && this->m_tan == _other.m_tan 
        && this->m_bit == _other.m_bit;
}

namespace std {

    std::size_t hash< NautilusVertex >::operator()(const NautilusVertex& _inst) const noexcept {
        std::size_t result = 0;
        nautilus::hashField(&result, _inst.m_pos);
        nautilus::hashField(&result, _inst.m_nor);
        nautilus::hashField(&result, _inst.m_tex);
        nautilus::hashField(&result, _inst.m_tan);
        nautilus::hashField(&result, _inst.m_bit);
        return result;
    }

}

#endif      // NAUTILUS_VULKAN_CPP