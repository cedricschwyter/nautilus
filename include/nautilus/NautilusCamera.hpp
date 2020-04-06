#ifndef NAUTILUS_CAMERA_HPP
#define NAUTILUS_CAMERA_HPP

#include "NautilusDefaults.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class NautilusCamera {
public:

    struct NautilusCameraVectors {
        glm::vec3 m_pos             = nautilus::defaults::WORLD_ORIGIN;
        glm::vec3 m_frt             = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 m_wup             = nautilus::defaults::WORLD_UP;
        glm::vec3 m_rgt             = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 m_cup             = nautilus::defaults::WORLD_UP;
    } m_cameraVectors;

    struct NautilusCameraEulerAngles {
        double m_yaw                = 0.0;
        double m_pitch              = 0.0;
        double m_roll               = 0.0;
    } m_angles;

    /**
     * Default constructor
     */ 
    NautilusCamera(void);

    /**
     * Constructor with position and alignment arguments
     * @param _vec The camera's initial vectors
     * @param _ang The camera's initial angles
     * @param _speed The camera's inital speed
     * @param _sens The camera's mouse response sensitivity
     * @param _fov The camera's inital field of view
     */ 
    NautilusCamera(
        NautilusCameraVectors       _vec,
        NautilusCameraEulerAngles   _ang,
        double                      _speed  = nautilus::defaults::CAMERA_SPEED,
        double                      _sens   = nautilus::defaults::CAMERA_SENS,
        double                      _fov    = nautilus::defaults::CAMERA_FOV);

    /**
     * Default destructor
     */ 
    ~NautilusCamera(void);

    /**
     * Handles keyboard input
     * Must be implemented by derived camera class
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
        int             _mods) = 0;

    /**
     * Handles mouse input
     * Must be implemented by derived camera class
     * @param _window A pointer to the GLFWwindow
     * @param _x The new x-coordinate relative to the left edge of the window
     * @param _y The new y-coordinate relative to the top edge of the window
     */ 
    virtual void mouseInput(GLFWwindow* _window, double _x, double _y) = 0;

    /**
     * Handles scroll input
     * Must be implemented by derived camera class
     * @param _window A pointer to the GLFWwindow
     * @param _dx The x-offset of the scroll wheel
     * @param _dy The y-offset of the scroll wheel
     */ 
    virtual void scrollInput(GLFWwindow* _window, double _dx, double _dy) = 0;

    /**
     * Returns the view matrix according to the current camera vectors
     * @return Returns the view matrix
     */ 
    virtual glm::mat4 view(void);

    /**
     * Updates the camera vectors according to movement and orientation
     */ 
    virtual void update(void);

private:

    double      m_speed             = 2.0;
    double      m_sens              = 0.1;
    double      m_fov               = 105.0;
    bool        m_inputEnabled      = true;
    bool        m_firstMouse        = true;

};

#endif      // NAUTILUS_CAMERA_HPP