#ifndef NAUTILUS_CAMERA_FOCUS_CPP
#define NAUTILUS_CAMERA_FOCUS_CPP

#include "NautilusCameraFocus.hpp"

NautilusCameraFocus::NautilusCameraFocus(glm::vec3 _focus) {
    this->m_focus = _focus;
}

NautilusCameraFocus::~NautilusCameraFocus() {
}

nautilus::NautilusStatus NautilusCameraFocus::focus(glm::vec3 _focus) {
    this->m_focus = _focus;
    return nautilus::NAUTILUS_STATUS_OK;
} 

void NautilusCameraFocus::key(
    GLFWwindow*     _window, 
    int             _key, 
    int             _scancode, 
    int             _action, 
    int             _mods) {
    if(_key == GLFW_KEY_W && _action == GLFW_PRESS) {
        this->move(nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_FORWARD);
        this->rotate(nautilus::NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_UP);
    }
    if(_key == GLFW_KEY_A && _action == GLFW_PRESS) {
        this->move(nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_LEFT);
        this->rotate(nautilus::NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_RGT, -1.0f);
    }
    if(_key == GLFW_KEY_S && _action == GLFW_PRESS) {
        this->move(nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_BACKWARD);
        this->rotate(nautilus::NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_UP, -1.0f);
    }
    if(_key == GLFW_KEY_D && _action == GLFW_PRESS) { 
        this->move(nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_RIGHT);
        this->rotate(nautilus::NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_RGT);
    }
}

void NautilusCameraFocus::cursor(GLFWwindow* _window, double _x, double _y) {
}

void NautilusCameraFocus::scroll(GLFWwindow* _window, double _dx, double _dy) {
    if(this->m_inputEnabled) {
        this->m_fov -= _dy;
        this->m_fov = std::clamp(this->m_fov, nautilus::defaults::CAMERA_MIN_FOV, nautilus::defaults::CAMERA_MAX_FOV);
    }
}

#endif      // NAUTILUS_CAMERA_FOCUS_CPP