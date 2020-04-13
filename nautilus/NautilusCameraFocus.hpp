#ifndef NAUTILUS_CAMERA_FOCUS_HPP
#define NAUTILUS_CAMERA_FOCUS_HPP

#include "NautilusCamera.hpp"

class NautilusCameraFocus 
    : public NautilusCamera {
public:

    /**
     * Constructor with arguments
     * @param _focus The focal point of the focus camera
     */ 
    NautilusCameraFocus(glm::vec3 _focus = nautilus::defaults::WORLD_ORIGIN);

    /**
     * Focuses the camera onto a point in world space
     * @param _focus The point to focus
     * @return Returns a nautilus::NautilusStatus status code
     */ 
    nautilus::NautilusStatus focus(glm::vec3 _focus);

    /**
     * Handles keyboard input
     * @param _window A pointer to the GLFWwindow
     * @param _key The GLFW keycode
     * @param _scancode  The system scancode of the key
     * @param _action The action (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT)
     * @param _mods Bitfield describing width modifier keys were held down
     */ 
    virtual void keyInput(
        GLFWwindow*     _window, 
        int             _key, 
        int             _scancode, 
        int             _action, 
        int             _mods);

    /**
     * Handles mouse input
     * @param _window A pointer to the GLFWwindow
     * @param _x The new x-coordinate relative to the left edge of the window
     * @param _y The new y-coordinate relative to the top edge of the window
     */ 
    virtual void mouseInput(GLFWwindow* _window, double _x, double _y);

    /**
     * Handles scroll input
     * @param _window A pointer to the GLFWwindow
     * @param _dx The x-offset of the scroll wheel
     * @param _dy The y-offset of the scroll wheel
     */ 
    virtual void scroll(GLFWwindow* _window, double _dx, double _dy);

    /**
     * Default destructor
     */ 
    ~NautilusCameraFocus(void);

private:

    glm::vec3 m_focus = nautilus::defaults::WORLD_ORIGIN;

};

#endif      // NAUTILUS_CAMERA_FOCUS_HPP