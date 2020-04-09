#ifndef NAUTILUS_CAMERA_2D_HPP
#define NAUTILUS_CAMERA_2D_HPP

#include "NautilusCamera.hpp"

class NautilusCamera2D
    : public NautilusCamera {
public:

    /**
     * Default constructor
     */ 
    NautilusCamera2D(void);

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
    virtual void scrollInput(GLFWwindow* _window, double _dx, double _dy);

    /**
     * Default destructor
     */ 
    ~NautilusCamera2D(void);

private:

};

#endif      // NAUTILUS_CAMERA_2D_HPP