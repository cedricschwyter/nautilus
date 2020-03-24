#ifndef NAUTILUS_OPENGL_SHELL_CPP
#define NAUTILUS_OPENGL_SHELL_CPP

#include "NautilusOpenGLShell.hpp"

NautilusOpenGLShell::NautilusOpenGLShell() {
}

void NautilusOpenGLShell::onAttach() {
}

void NautilusOpenGLShell::onRender() {
}

NautilusStatus NautilusOpenGLShell::createWindow() {
    if(!this->m_windowCreated) {
        nautilus::logger::log("Creating GLFWwindow...");
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        this->m_monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(this->m_monitor);
        if(this->m_shellContext == NAUTILUS_SHELL_CONTEXT_WINDOWED) {
            this->m_window = glfwCreateWindow(
                this->m_width,
                this->m_height,
                this->m_title.c_str(),
                nullptr,
                nullptr);
            glfwSetWindowPos(
                this->m_window,
                mode->width / 2 - this->m_width / 2,
                mode->height / 2 - this->m_height / 2);
        }
        else if(this->m_shellContext == NAUTILUS_SHELL_CONTEXT_FULLSCREEN) {
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
            this->m_window = glfwCreateWindow(
                mode->width,
                mode->height,
                this->m_title.c_str(),
                this->m_monitor,
                nullptr);
        }
        else if(this->m_shellContext == NAUTILUS_SHELL_CONTEXT_BORDERLESS) {
            this->m_window = glfwCreateWindow(
                mode->width,
                mode->height,
                this->m_title.c_str(),
                this->m_monitor,
                nullptr);
        }
        if(this->m_window == nullptr) {
            nautilus::logger::log("Failed to create GLFWwindow", NAUTILUS_STATUS_FATAL);
            return NAUTILUS_STATUS_FATAL;
        }
        glfwMakeContextCurrent(this->m_window);
        GLFWimage windowIcon[1];
        windowIcon[0].pixels = nautilus::loadSTBI(
            this->m_shellIconPath,
            &windowIcon[0].width,
            &windowIcon[0].height,
            0,
            4);
        glfwSetWindowIcon(this->m_window, 1, windowIcon);
        nautilus::freeSTBI(windowIcon[0].pixels);
        glfwSetWindowUserPointer(this->m_window, this);
        this->m_windowCreated = true;
        nautilus::logger::log("Successfully created GLFWwindow");
        initAPI();
    }
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusOpenGLShell::initAPI() {
    if(!this->m_initializedAPI) {
        nautilus::logger::log("Initializing OpenGL...");
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            nautilus::logger::log("Failed to load OpenGL function pointers through GLAD", NAUTILUS_STATUS_FATAL);
            return NAUTILUS_STATUS_FATAL;
        }
        glViewport(0, 0, this->m_width, this->m_height);
        glfwShowWindow(this->m_window);
        glfwFocusWindow(this->m_window);
        nautilus::logger::log("Successfully initialized OpenGL");
        this->m_initializedAPI = true;
    }
    return NAUTILUS_STATUS_OK;
}

NautilusOpenGLShell::~NautilusOpenGLShell() {
    
}

#endif      // NAUTILUS_OPENGL_SHELL_CPP