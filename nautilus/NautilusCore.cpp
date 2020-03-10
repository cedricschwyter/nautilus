#ifndef NAUTILUS_CORE_CPP
#define NAUTILUS_CORE_CPP

#include "NautilusCore.hpp"

NautilusCore::NautilusCore() {
    glfwInit();
}

NautilusStatus NautilusCore::attachShell(NautilusShell* _shell) {
    this->m_shell = _shell;
    this->m_shell->onAttach();
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::loop() {
    return NAUTILUS_STATUS_OK;
}

NautilusCore::~NautilusCore() {
    
}

#endif      // NAUTILUS_CORE_CPP