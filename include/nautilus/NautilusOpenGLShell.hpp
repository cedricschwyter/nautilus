#ifndef NAUTILUS_OPENGL_SHELL_HPP
#define NAUTILUS_OPENGL_SHELL_HPP

#include "NautilusShell.hpp"
#include "NautilusNS.hpp"

class NautilusOpenGLShell
    : public NautilusShell {
    using NautilusShell::NautilusShell;
public:

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
     * Creates an OpenGL-capable GLFW-window
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus createWindow(void);

    /**
     * Initializes the OpenGL API
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus initAPI(void);

};

#endif      // NAUTILUS_OPENGL_SHELL_HPP