#ifndef NAUTILUS_SHELL_CPP
#define NAUTILUS_SHELL_CPP

#include "NautilusShell.hpp"
#include "NautilusNS.hpp"

#include <iostream>

NautilusShell::NautilusShell() {

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
    std::scoped_lock< std::mutex > lock(m_attachedMutex);
    this->m_attached = false;
    std::scoped_lock< std::mutex > shellsLock(nautilus::shellsLock);
    std::vector< NautilusShell* >::iterator it = nautilus::shells.begin();
    std::advance(it, this->m_id);
    nautilus::shells.erase(it);
    glfwDestroyWindow(this->m_window);
    return NAUTILUS_STATUS_OK;
}

NautilusShell::~NautilusShell() {
}

#endif      // NAUTILUS_SHELL_CPP