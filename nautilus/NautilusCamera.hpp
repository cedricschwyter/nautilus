#ifndef NAUTILUS_CAMERA_HPP
#define NAUTILUS_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class NautilusCamera {
public:

    /**
     * Default constructor
     */ 
    NautilusCamera(void);

    /**
     * Default destructor
     */ 
    ~NautilusCamera(void);

    /**
     * Returns the view matrix according to the current camera vectors
     * @return Returns the view matrix
     */ 
    glm::mat4 view(void);

    /**
     * Updates the camera vectors according to movement and orientation
     */ 
    virtual void update(void);

private:

    struct NautilusCameraVectors {
        glm::vec3 m_pos             = glm::vec3(0.0f);
        glm::vec3 m_frt             = glm::vec3(0.0f);
        glm::vec3 m_wup             = glm::vec3(0.0f);
        glm::vec3 m_rgt             = glm::vec3(0.0f);
        glm::vec3 m_cup             = glm::vec3(0.0f);
    } m_cameraVectors;

    struct NautilusCameraEulerAngles {
        double m_yaw                = 0.0;
        double m_pitch              = 0.0;
        double m_roll               = 0.0;
    } m_angles;

    double      m_speed             = 2.0;
    double      m_sens              = 0.1;
    double      m_fov               = 105.0;
    bool        m_inputEnabled      = true;
    bool        m_firstMouse        = true;

};

#endif      // NAUTILUS_CAMERA_HPP