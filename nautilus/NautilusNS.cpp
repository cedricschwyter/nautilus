#ifndef NAUTILUS_NS_CPP
#define NAUTILUS_NS_CPP

#define STB_IMAGE_IMPLEMENTATION
#include "../ext/stb/stb_image.h"

#include "NautilusNS.hpp"

namespace nautilus {

    NautilusInterface interface = NAUTILUS_INTERFACE_DEFAULT;

    NautilusStatus nautilusSetInterface(NautilusInterface _interface) {
        nautilus::interface = _interface;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus initializeGLFW() {
        glfwInit();
        return NAUTILUS_STATUS_OK;
    }

    GLFWwindow* createGLFWwindow(uint32_t _w, uint32_t _h, std::string _title, unsigned char* _icon) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        if(nautilus::interface == NAUTILUS_INTERFACE_OPENGL)
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        else if(nautilus::interface == NAUTILUS_INTERFACE_VULKAN)
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        return nullptr;
    }

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

}

#endif      // NAUTILUS_NS_CPP