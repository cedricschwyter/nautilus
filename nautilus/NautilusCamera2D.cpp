#ifndef NAUTILUS_CAMERA_2D_CPP
#define NAUTILUS_CAMERA_2D_CPP

#include "NautilusCamera2D.hpp"

namespace nautilus {

    NautilusCamera2D::NautilusCamera2D() {
    }

    void NautilusCamera2D::key(
        GLFWwindow*     _window, 
        int             _key, 
        int             _scancode, 
        int             _action, 
        int             _mods) {
        if(_key == GLFW_KEY_W && _action == GLFW_PRESS) this->move(nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_FORWARD);
        if(_key == GLFW_KEY_A && _action == GLFW_PRESS) this->move(nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_LEFT);
        if(_key == GLFW_KEY_S && _action == GLFW_PRESS) this->move(nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_BACKWARD);
        if(_key == GLFW_KEY_D && _action == GLFW_PRESS) this->move(nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_RIGHT);
    }

    void NautilusCamera2D::cursor(GLFWwindow* _window, double _x, double _y) {
    }

    void NautilusCamera2D::scroll(GLFWwindow* _window, double _dx, double _dy) {
        if(this->m_inputEnabled) {
            this->m_fov -= static_cast< float >(_dy);
            this->m_fov = std::clamp(this->m_fov, nautilus::defaults::CAMERA_MIN_FOV, nautilus::defaults::CAMERA_MAX_FOV);
        }
    }
}

#endif      // NAUTILUS_CAMERA_2D_CPP