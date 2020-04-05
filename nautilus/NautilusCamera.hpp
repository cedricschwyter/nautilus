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

};

#endif      // NAUTILUS_CAMERA_HPP