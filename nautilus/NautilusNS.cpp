#ifndef NAUTILUS_NS_CPP
#define NAUTILUS_NS_CPP

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "NautilusNS.hpp"

namespace nautilus {

    uint32_t FPS = 60;

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

    NautilusStatus nautilusSetFramerate(uint32_t _fps) {
        nautilus::FPS = _fps;
        return NAUTILUS_STATUS_OK;
    }

}

#endif      // NAUTILUS_NS_CPP