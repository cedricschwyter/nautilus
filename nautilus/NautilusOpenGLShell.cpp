#ifndef NAUTILUS_OPENGL_SHELL_CPP
#define NAUTILUS_OPENGL_SHELL_CPP

#include "NautilusOpenGLShell.hpp"

NautilusOpenGLShell::NautilusOpenGLShell() {
    this->m_API = nautilus::NAUTILUS_API_OPENGL;
}

void NautilusOpenGLShell::onAttach() {
}

void NautilusOpenGLShell::onRender() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

nautilus::NautilusStatus NautilusOpenGLShell::render() {
    this->onRender();
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusOpenGLShell::setDefaultWindowHints() {
    this->m_title = "Standard OpenGL Example with nautilus by D3PSI";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusOpenGLShell::initAPI() {
    if(this->m_initializedAPI) return nautilus::NAUTILUS_STATUS_OK;
    nautilus::logger::log("Initializing OpenGL...");
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        nautilus::logger::log("Failed to load OpenGL function pointers through GLAD", nautilus::NAUTILUS_STATUS_FATAL);
        return nautilus::NAUTILUS_STATUS_FATAL;
    }
    glViewport(0, 0, this->m_width, this->m_height);
    glfwShowWindow(this->m_window);
    glfwFocusWindow(this->m_window);
    nautilus::logger::log("Successfully initialized OpenGL");
    this->m_initializedAPI = true;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusOpenGLShell::clean() {
    glfwDestroyWindow(this->m_window);
    return nautilus::NAUTILUS_STATUS_OK;
}

#endif      // NAUTILUS_OPENGL_SHELL_CPP