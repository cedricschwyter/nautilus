#ifndef NAUTILUS_CORE_CPP
#define NAUTILUS_CORE_CPP

#include "NautilusCore.hpp"
#include "NautilusNS.hpp"

NautilusCore::NautilusCore() {
    glfwInit();
}

NautilusStatus NautilusCore::attachShell(NautilusShell* _shell) {
    _shell->createWindow();
    _shell->onAttach();
    std::scoped_lock< std::mutex > shellLock(nautilus::shellsLock);
    nautilus::shells.push_back(_shell);
    std::scoped_lock< std::mutex > lock(_shell->attachedMutex);
    _shell->attached = true;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::start() {
    t0 = std::thread(&NautilusCore::loop, this);
    t0.detach();
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::loop() {
    while(!nautilus::exit) {
        std::scoped_lock< std::mutex > shellLock(nautilus::shellsLock);
        for(NautilusShell* shell : nautilus::shells) {
            std::scoped_lock< std::mutex > lock(shell->attachedMutex);
            if(shell->attached) {
                glfwMakeContextCurrent(shell->m_window);
                shell->onRender();
                glfwSwapBuffers(shell->m_window);
                glfwPollEvents();
            }
        }
    }
    glfwTerminate();
    return NAUTILUS_STATUS_OK;
}

NautilusCore::~NautilusCore() {
    
}

#endif      // NAUTILUS_CORE_CPP