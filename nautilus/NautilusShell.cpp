#ifndef NAUTILUS_SHELL_CPP
#define NAUTILUS_SHELL_CPP

#include "NautilusShell.hpp"
#include "NautilusNS.hpp"

#include <iostream>

NautilusShell::NautilusShell() {
}

void NautilusShell::onDetach(GLFWwindow* _window) {
    nautilus::logger::log("onDetach");
}

void NautilusShell::onResize(GLFWwindow* _window, int _w, int _h) {
    nautilus::logger::log("onResize");
}

void NautilusShell::onFocus(GLFWwindow* _window, int _focus) {
    nautilus::logger::log("onFocus");
}

void NautilusShell::onIconify(GLFWwindow* _window, int _iconify) {
    nautilus::logger::log("onIconify");
}

void NautilusShell::onCursor(GLFWwindow* _window, double _x, double _y) {
    nautilus::logger::log("onCursor");
}

void NautilusShell::onCursorIn(GLFWwindow* _window, int _enter) {
    nautilus::logger::log("onCursorIn");
}

void NautilusShell::onKey(
    GLFWwindow*     _window, 
    int             _key, 
    int             _scancode, 
    int             _action, 
    int             _mods) {
    if(_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->m_window, GLFW_TRUE);
    }
}

void NautilusShell::onScroll(GLFWwindow* _window, double _dx, double _dy) {
    nautilus::logger::log("onScroll");
}

NautilusStatus NautilusShell::setShellContext(NautilusShellContext _context) {
    this->m_shellContext = _context;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::setShellTitle(std::string _title) {
    this->m_title = _title;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::setShellExtent(uint32_t _width, uint32_t _height) {
    this->m_width = _width;
    this->m_height = _height;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::setShellIcon(std::string _path) {
    this->m_shellIconPath = _path;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::detach() {
    this->onDetach(this->m_window);
    std::scoped_lock< std::mutex > lock(m_attachedLock);
    this->m_attached = false;
    glfwDestroyWindow(this->m_window);
    std::scoped_lock< std::mutex > shellCountLock(nautilus::shellCountLock);
    nautilus::shellCount--;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::setCallbacks() {
    if(!this->m_callbacksSet) {
        glfwSetFramebufferSizeCallback(this->m_window, nautilus::dispatcher::onResize);
        glfwSetWindowFocusCallback(this->m_window, nautilus::dispatcher::onFocus);
        glfwSetWindowIconifyCallback(this->m_window, nautilus::dispatcher::onIconify);
        glfwSetCursorPosCallback(this->m_window, nautilus::dispatcher::onCursor);
        glfwSetCursorEnterCallback(this->m_window, nautilus::dispatcher::onCursorIn);
        glfwSetKeyCallback(this->m_window, nautilus::dispatcher::onKey);
        this->m_callbacksSet = true;
    }
    return NAUTILUS_STATUS_OK;
}

NautilusShell::~NautilusShell() {
}

#endif      // NAUTILUS_SHELL_CPP