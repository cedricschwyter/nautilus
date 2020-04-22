#ifndef NAUTILUS_SHELL_OPENGL_HPP
#define NAUTILUS_SHELL_OPENGL_HPP

#include "NautilusShell.hpp"
#include "NautilusNS.hpp"
#include "NautilusAPI.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class NautilusShellOpenGL
    : public NautilusShell {
public:

    /**
     * Default constructor
     */ 
    NautilusShellOpenGL(void);

    /**
     * Gets executed when the shell gets attached to the core
     * @return Returns a NautilusStatus status code
     */
    virtual void onAttach(void);

    /**
     * Gets executed at the specified frequency by the application loop
     * Computes rendering operations
     * @return Returns a NautilusStatus status code
     */ 
    virtual void onRender(void);

    /**
     * Cleans all allocated OpenGL resources by the shell
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus clean(void);

    /**
     * Executes OpenGL rendering routine
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus render(void);

    /**
     * Updates the viewport dynamically
     * @param _viewport The viewport extent data
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus updateShellViewport(const nautilus::NautilusViewport& _viewport);

    /**
     * Sets the default window hints for the corresponding API
     * @return Returns a NautilusStatus status code
     */ 
    virtual nautilus::NautilusStatus setAPIWindowHints(void);

    /**
     * Initializes the OpenGL API
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus initAPI(void);

    /**
     * Default destructor
     */ 
    ~NautilusShellOpenGL(void);

};

#endif      // NAUTILUS_SHELL_OPENGL_HPP