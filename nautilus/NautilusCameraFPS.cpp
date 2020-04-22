#ifndef NAUTILUS_CAMERA_FPS_CPP
#define NAUTILUS_CAMERA_FPS_CPP

#include "NautilusCameraFPS.hpp"

NautilusCameraFPS::NautilusCameraFPS() {
}

NautilusCameraFPS::~NautilusCameraFPS() {
}

void NautilusCameraFPS::key(
    GLFWwindow*     _window, 
    int             _key, 
    int             _scancode, 
    int             _action, 
    int             _mods) {
    if(_key == GLFW_KEY_W && _action == GLFW_PRESS) move(nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_FORWARD);
    if(_key == GLFW_KEY_A && _action == GLFW_PRESS) move(nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_LEFT);
    if(_key == GLFW_KEY_S && _action == GLFW_PRESS) move(nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_BACKWARD);
    if(_key == GLFW_KEY_D && _action == GLFW_PRESS) move(nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_RIGHT);
}

void NautilusCameraFPS::cursor(GLFWwindow* _window, double _x, double _y) {
    static double lastX = 0.0;
    static double lastY = 0.0;
    if(m_inputEnabled) {
        double xOff;
        double yOff;
        if(m_firstMouse) {
            xOff = 0;
            yOff = 0;
            m_firstMouse = false;
        } else {
            xOff = _x - lastX;
            yOff = _y - lastY;
        }
        lastX = _x;
        lastY = _y;
        xOff *= m_sens;
        yOff *= m_sens;
        m_angles.m_yaw += static_cast< float >(xOff);
        m_angles.m_pitch += static_cast< float >(yOff);
        m_angles.m_pitch = std::clamp(m_angles.m_pitch, nautilus::defaults::CAMERA_MIN_PITCH, nautilus::defaults::CAMERA_MAX_PITCH);
        update();
    }
}

void NautilusCameraFPS::scroll(GLFWwindow* _window, double _dx, double _dy) {
    if(m_inputEnabled) {
        m_fov -= static_cast< float >(_dy);
        m_fov = std::clamp(m_fov, nautilus::defaults::CAMERA_MIN_FOV, nautilus::defaults::CAMERA_MAX_FOV);
    }
}

#endif      // NAUTILUS_CAMERA_FPS_CPP