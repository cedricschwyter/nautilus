#ifndef NAUTILUS_OPENGL_SHELL_HPP
#define NAUTILUS_OPENGL_SHELL_HPP

#include "NautilusShell.hpp"
#include "NautilusNS.hpp"

class NautilusOpenGLShell
    : public NautilusShell {
public:

    /**
     * Default constructor
     */
    NautilusOpenGLShell(void);

    /**
     * Creates an OpenGL-capable GLFW-window
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus createWindow(void);

    /**
     * Default destructor
     */ 
    ~NautilusOpenGLShell(void);

};

#endif      // NAUTILUS_OPENGL_SHELL_HPP