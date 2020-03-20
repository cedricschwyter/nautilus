#ifndef NAUTILUS_SHELL_CPP
#define NAUTILUS_SHELL_CPP

#include "NautilusShell.hpp"
#include "NautilusNS.hpp"

#include <iostream>

NautilusShell::NautilusShell() {
}

void NautilusShell::onDetach(GLFWwindow* _window) {
}

void NautilusShell::onResize(GLFWwindow* _window, int _w, int _h) {
}

void NautilusShell::onFocus(GLFWwindow* _window, int _focus) {
}

void NautilusShell::onIconify(GLFWwindow* _window, int _iconify) {
}

void NautilusShell::onCursor(GLFWwindow* _window, double _x, double _y) {
}

void NautilusShell::onCursorIn(GLFWwindow* _window, int _enter) {
}

void NautilusShell::onKey(
    GLFWwindow*     _window, 
    int             _key, 
    int             _scancode, 
    int             _action, 
    int             _mods) {
}

void NautilusShell::onScroll(GLFWwindow* _window, double _dx, double _dy) {
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

NautilusStatus NautilusShell::events() {
    if(glfwGetKey(this->m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->m_window, GLFW_TRUE);
    }
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::detach() {
    std::scoped_lock< std::mutex > lock(m_attachedLock);
    this->m_attached = false;
    glfwDestroyWindow(this->m_window);
    std::scoped_lock< std::mutex > shellCountLock(nautilus::shellCountLock);
    nautilus::shellCount--;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::setCallbacks() {
    glfwSetWindowCloseCallback(this->m_window, nautilus::dispatcher::onDetach);
    glfwSetFramebufferSizeCallback(this->m_window, nautilus::dispatcher::onResize);
    glfwSetWindowFocusCallback(this->m_window, nautilus::dispatcher::onFocus);
    glfwSetWindowIconifyCallback(this->m_window, nautilus::dispatcher::onIconify);
    glfwSetCursorPosCallback(this->m_window, nautilus::dispatcher::onCursor);
    glfwSetCursorEnterCallback(this->m_window, nautilus::dispatcher::onCursorIn);
    glfwSetKeyCallback(this->m_window, nautilus::dispatcher::onKey);
    return NAUTILUS_STATUS_OK;
}

NautilusShell::~NautilusShell() {
}

#endif      // NAUTILUS_SHELL_CPP