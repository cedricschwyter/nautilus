#ifndef NAUTILUS_CORE_CPP
#define NAUTILUS_CORE_CPP

#include "NautilusCore.hpp"
#include "NautilusNS.hpp"

NautilusCore::NautilusCore() {

}

NautilusStatus NautilusCore::attachShell(NautilusShell* _shell) {
    std::unique_lock< std::mutex > shellLock(nautilus::shellsLock);
    nautilus::shells.push_back(_shell);
    shellLock.unlock();
    _shell->onAttach();
    std::unique_lock< std::mutex > lock(_shell->attachedMutex);
    _shell->attached = true;
    lock.unlock();
    start();
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::start() {
    if(!nautilus::running) {
        nautilus::running = true;
        t0 = std::thread(&NautilusCore::loop, this);
        t0.detach();
    }
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::loop() {
    glfwInit();
    while(!nautilus::exit && nautilus::running) {
        std::scoped_lock< std::mutex > shellLock(nautilus::shellsLock);
        for(NautilusShell* shell : nautilus::shells) {
            std::scoped_lock< std::mutex > lock(shell->attachedMutex);
            if(shell->attached) {
                shell->createWindow();
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