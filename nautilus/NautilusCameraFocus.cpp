#ifndef NAUTILUS_CAMERA_FOCUS_CPP
#define NAUTILUS_CAMERA_FOCUS_CPP

#include "NautilusCameraFocus.hpp"

namespace nautilus {

    NautilusCameraFocus::NautilusCameraFocus(glm::vec3 _focus) {
        m_focus = _focus;
    }

    NautilusCameraFocus::~NautilusCameraFocus() {
    }

    NautilusStatus NautilusCameraFocus::focus(glm::vec3 _focus) {
        m_focus = _focus;
        return NAUTILUS_STATUS_OK;
    } 

    void NautilusCameraFocus::key(
        GLFWwindow*     _window, 
        int             _key, 
        int             _scancode, 
        int             _action, 
        int             _mods) {
        if(_key == GLFW_KEY_W && _action == GLFW_PRESS) {
            move(NAUTILUS_CAMERA_MOVEMENT_DIRECTION_FORWARD);
            rotate(NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_UP);
        }
        if(_key == GLFW_KEY_A && _action == GLFW_PRESS) {
            move(NAUTILUS_CAMERA_MOVEMENT_DIRECTION_LEFT);
            rotate(NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_RGT, -1.0f);
        }
        if(_key == GLFW_KEY_S && _action == GLFW_PRESS) {
            move(NAUTILUS_CAMERA_MOVEMENT_DIRECTION_BACKWARD);
            rotate(NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_UP, -1.0f);
        }
        if(_key == GLFW_KEY_D && _action == GLFW_PRESS) { 
            move(NAUTILUS_CAMERA_MOVEMENT_DIRECTION_RIGHT);
            rotate(NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_RGT);
        }
    }

    void NautilusCameraFocus::cursor(GLFWwindow* _window, double _x, double _y) {
    }

    void NautilusCameraFocus::scroll(GLFWwindow* _window, double _dx, double _dy) {
        if(m_inputEnabled) {
            m_fov -= _dy;
            m_fov = std::clamp(m_fov, defaults::CAMERA_MIN_FOV, defaults::CAMERA_MAX_FOV);
        }
    }

}

#endif      // NAUTILUS_CAMERA_FOCUS_CPP