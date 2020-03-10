#ifndef NAUTILUS_OPENGL_SHELL_CPP
#define NAUTILUS_OPENGL_SHELL_CPP

#include "NautilusOpenGLShell.hpp"

NautilusOpenGLShell::NautilusOpenGLShell() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
}

NautilusOpenGLShell::~NautilusOpenGLShell() {
    
}

#endif      // NAUTILUS_OPENGL_SHELL_CPP