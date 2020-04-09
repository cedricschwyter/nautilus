#ifndef NAUTILUS_CAMERA_FPS_CPP
#define NAUTILUS_CAMERA_FPS_CPP

#include "NautilusCameraFPS.hpp"

NautilusCameraFPS::NautilusCameraFPS() {
}

NautilusCameraFPS::~NautilusCameraFPS() {
}

void NautilusCameraFPS::keyInput(
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

void NautilusCameraFPS::mouseInput(GLFWwindow* _window, double _x, double _y) {
    static double lastX = 0.0;
    static double lastY = 0.0;
    if(this->m_inputEnabled) {
        double xOff;
        double yOff;
        if(this->m_firstMouse) {
            xOff = 0;
            yOff = 0;
            this->m_firstMouse = false;
        } else {
            xOff = _x - lastX;
            yOff = _y - lastY;
        }
        lastX = _x;
        lastY = _y;
        xOff *= this->m_sens;
        yOff *= this->m_sens;
        this->m_angles.m_yaw += xOff;
        this->m_angles.m_pitch += yOff;
        this->m_angles.m_pitch = std::clamp(this->m_angles.m_pitch, nautilus::defaults::CAMERA_MIN_PITCH, nautilus::defaults::CAMERA_MAX_PITCH);
        this->update();
    }
}

void NautilusCameraFPS::scrollInput(GLFWwindow* _window, double _dx, double _dy) {
    if(this->m_inputEnabled) {
        this->m_fov -= _dy;
        this->m_fov = std::clamp(this->m_fov, nautilus::defaults::CAMERA_MIN_FOV, nautilus::defaults::CAMERA_MAX_FOV);
    }
}

#endif      // NAUTILUS_CAMERA_FPS_CPP