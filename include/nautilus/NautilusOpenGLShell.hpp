#ifndef NAUTILUS_OPENGL_SHELL_HPP
#define NAUTILUS_OPENGL_SHELL_HPP

#include "NautilusShell.hpp"
#include "NautilusNS.hpp"
#include "NautilusAPI.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class NautilusOpenGLShell
    : public NautilusShell {
public:

    /**
     * Default constructor
     */ 
    NautilusOpenGLShell(void);

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
    NautilusStatus clean(void);

    /**
     * Executes OpenGL rendering routine
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus render(void);

    /**
     * Sets the default window hints for the corresponding API
     * @return Returns a NautilusStatus status code
     */ 
    virtual NautilusStatus setDefaultWindowHints(void);

    /**
     * Initializes the OpenGL API
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus initAPI(void);

    /**
     * Default destructor
     */ 
    ~NautilusOpenGLShell(void) = default;

};

#endif      // NAUTILUS_OPENGL_SHELL_HPP