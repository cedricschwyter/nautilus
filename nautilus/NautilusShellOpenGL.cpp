#ifndef NAUTILUS_SHELL_OPENGL_CPP
#define NAUTILUS_SHELL_OPENGL_CPP

#include "NautilusShellOpenGL.hpp"

namespace nautilus {

    NautilusShellOpenGL::NautilusShellOpenGL() {
        m_api = NAUTILUS_API_OPENGL;
    }

    NautilusShellOpenGL::~NautilusShellOpenGL() {
    }

    void NautilusShellOpenGL::onAttach() {
    }

    void NautilusShellOpenGL::onRender() {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    NautilusStatus NautilusShellOpenGL::render() {
        printStats();
        onRender();
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShellOpenGL::setAPIWindowHints() {
        m_title = defaults::CONTEXT_NAME_OPENGL;
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShellOpenGL::initAPI() {
        if(m_initializedAPI) return NAUTILUS_STATUS_OK;
        logger::log("Initializing OpenGL...");
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            logger::log("Failed to load OpenGL function pointers through GLAD", NAUTILUS_STATUS_FATAL);
            return NAUTILUS_STATUS_FATAL;
        }
        glfwMakeContextCurrent(m_window);
        glViewport(0, 0, m_width, m_height);
        glfwShowWindow(m_window);
        glfwFocusWindow(m_window);
        logger::log("Successfully initialized OpenGL");
        m_initializedAPI = true;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShellOpenGL::clean() {
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShellOpenGL::updateShellViewport(const NautilusViewport& _viewport) {
        return NAUTILUS_STATUS_OK;
    }

}

#endif      // NAUTILUS_SHELL_OPENGL_CPP