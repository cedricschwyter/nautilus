#ifndef NAUTILUS_OPENGL_SHELL_CPP
#define NAUTILUS_OPENGL_SHELL_CPP

#include "NautilusOpenGLShell.hpp"

NautilusOpenGLShell::NautilusOpenGLShell() {
    m_api = nautilus::NAUTILUS_API_OPENGL;
}

NautilusOpenGLShell::~NautilusOpenGLShell() {
}

void NautilusOpenGLShell::onAttach() {
}

void NautilusOpenGLShell::onRender() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

nautilus::NautilusStatus NautilusOpenGLShell::render() {
    printStats();
    onRender();
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusOpenGLShell::setAPIWindowHints() {
    m_title = "Standard OpenGL Example with nautilus by D3PSI";
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusOpenGLShell::initAPI() {
    if(m_initializedAPI) return nautilus::NAUTILUS_STATUS_OK;
    nautilus::logger::log("Initializing OpenGL...");
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        nautilus::logger::log("Failed to load OpenGL function pointers through GLAD", nautilus::NAUTILUS_STATUS_FATAL);
        return nautilus::NAUTILUS_STATUS_FATAL;
    }
    glViewport(0, 0, m_width, m_height);
    glfwShowWindow(m_window);
    glfwFocusWindow(m_window);
    nautilus::logger::log("Successfully initialized OpenGL");
    m_initializedAPI = true;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusOpenGLShell::clean() {
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusOpenGLShell::updateShellViewport(const nautilus::NautilusViewport& _viewport) {
    return nautilus::NAUTILUS_STATUS_OK;
}

#endif      // NAUTILUS_OPENGL_SHELL_CPP