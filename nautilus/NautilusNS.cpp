#ifndef NAUTILUS_NS_CPP
#define NAUTILUS_NS_CPP

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "NautilusNS.hpp"

namespace nautilus {

    uint32_t                                    FPS             = 60;
    bool                                        exit            = false;
    std::mutex                                  exitLock;
    bool                                        running         = false;
    std::mutex                                  runningLock;
    std::vector< NautilusShell* >               shells;
    std::mutex                                  shellsLock;
    std::vector< std::thread* >                 threadpool;
    std::mutex                                  threadpoolLock;
    uint32_t                                    shellCount      = 0;
    std::mutex                                  shellCountLock;
    
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

    template< typename T >
    std::pair< bool, int32_t > getIndexOfElement(const std::vector< T >& _vec, const T& _element) {
        std::pair< bool, int32_t > result;
        auto it = std::find(_vec.begin(), _vec.end(), _element);
        if (it != _vec.end()) {
            result.second = std::distance(_vec.begin(), it);
            result.first = true;
        }
        else {
            result.first = false;
            result.second = -1;
        }
        return result;
    }

    template< typename T >
    std::pair< bool, int32_t > getIndexOfElement(const std::vector< T* >& _vec, const T* _element) {
        std::pair< bool, int32_t > result;
        auto it = std::find(_vec.begin(), _vec.end(), _element);
        if (it != _vec.end()) {
            result.second = std::distance(_vec.begin(), it);
            result.first = true;
        }
        else {
            result.first = false;
            result.second = -1;
        }
        return result;
    }

}

#endif      // NAUTILUS_NS_CPP