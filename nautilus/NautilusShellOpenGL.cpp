#ifndef NAUTILUS_SHELL_OPENGL_CPP
#define NAUTILUS_SHELL_OPENGL_CPP

#include "NautilusShellOpenGL.hpp"

NautilusShellOpenGL::NautilusShellOpenGL() {
    m_api = nautilus::NAUTILUS_API_OPENGL;
}

NautilusShellOpenGL::~NautilusShellOpenGL() {
}

void NautilusShellOpenGL::onAttach() {
}

void NautilusShellOpenGL::onRender() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

nautilus::NautilusStatus NautilusShellOpenGL::render() {
    printStats();
    onRender();
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShellOpenGL::setAPIWindowHints() {
    m_title = nautilus::defaults::CONTEXT_NAME_OPENGL;
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShellOpenGL::initAPI() {
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

nautilus::NautilusStatus NautilusShellOpenGL::clean() {
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShellOpenGL::updateShellViewport(const nautilus::NautilusViewport& _viewport) {
    return nautilus::NAUTILUS_STATUS_OK;
}

#endif      // NAUTILUS_SHELL_OPENGL_CPP