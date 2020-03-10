#ifndef NAUTILUS_SHELL_CPP
#define NAUTILUS_SHELL_CPP

#include "NautilusShell.hpp"
#include "NautilusNS.hpp"

#include <iostream>

NautilusShell::NautilusShell() {
    createWindow();
}

NautilusStatus NautilusShell::createWindow() {
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
    return NAUTILUS_STATUS_OK;
}

NautilusShell::~NautilusShell() {
    
}

#endif      // NAUTILUS_SHELL_CPP