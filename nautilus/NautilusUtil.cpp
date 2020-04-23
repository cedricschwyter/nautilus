#ifndef NAUTILUS_UTIL_CPP
#define NAUTILUS_UTIL_CPP

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "NautilusUtil.hpp"
#include "NautilusCore.hpp"

namespace nautilus {

    namespace util {

        unsigned char* loadSTBI(
            std::string _path, 
            int*        _x, 
            int*        _y, 
            int*        _comp, 
            int         _req_comp) {
            return reinterpret_cast<unsigned char*>(stbi_load(
                        _path.c_str(),
                        _x,
                        _y,
                        _comp,
                        _req_comp));
        }

        NautilusStatus freeSTBI(unsigned char* _pixels) {
            stbi_image_free(_pixels);
            return NAUTILUS_STATUS_OK;
        }

        VkCommandBuffer startVulkanCommandBuffer(const NautilusVulkanQueueType& _queue) {
            return VkCommandBuffer();
        }

        NautilusStatus endVulkanCommandBuffer(const VkCommandBuffer& _cmdBuf) {
            return NAUTILUS_STATUS_OK;
        }

        template< typename _T >
        std::size_t hashField(std::size_t* _hash, const _T& _field) {
            std::hash< _T > hashFunc;
            *_hash ^= hashFunc(_field) + 0x9e3779b9 + (*_hash << 6) + (*_hash >> 2);
            return *_hash;
        }
        
        const std::vector< char > loadFile(const std::string& _path) {
            logger::log("Loading file at '" + _path + "'");
            std::ifstream file(_path, std::ios::ate | std::ios::binary);        // Start reading at end of file --> determine the buffer size needed
            if(!file.is_open()) 
                logger::log("Failed to load file at '" + _path + "'");
            size_t bufferSize = (size_t)file.tellg();        // Find read position and thus necessary buffer size
            std::vector< char > buffer(bufferSize);
            file.seekg(0);        // Translate back to the beginning of the file
            file.read(buffer.data(), bufferSize);
            file.close();
            logger::log("Loaded file at '" + _path + "'");
            return buffer;
        }

    }

}

#endif      // NAUTILUS_UTIL_CPP