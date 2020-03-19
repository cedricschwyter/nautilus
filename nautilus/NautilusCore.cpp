#ifndef NAUTILUS_CORE_CPP
#define NAUTILUS_CORE_CPP

#include "NautilusCore.hpp"
#include "NautilusNS.hpp"

NautilusCore::NautilusCore() {
}

NautilusStatus NautilusCore::attachShell(NautilusShell* _shell) {
    static int32_t id = 0;
    std::unique_lock< std::mutex > idLock(_shell->m_idLock);
    _shell->m_id = id;
    idLock.unlock();
    id++;
    nautilus::shellCount++;
    std::unique_lock< std::mutex > shellLock(nautilus::shellsLock);
    nautilus::shells.push_back(_shell);
    shellLock.unlock();
    _shell->onAttach();
    std::unique_lock< std::mutex > lock(_shell->m_attachedLock);
    _shell->m_attached = true;
    lock.unlock();
    if(!nautilus::running) {
        nautilus::running = true;
        m_t0 = new std::thread(&NautilusCore::loop, this);
    }
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::loop() {
    glfwInit();
    std::unique_lock< std::mutex > exitLock(nautilus::exitLock);
    while(!nautilus::exit && nautilus::running) {
        exitLock.unlock();
        std::unique_lock< std::mutex > shellLock(nautilus::shellsLock);
        for(NautilusShell* shell : nautilus::shells) {
            shellLock.unlock();
            std::unique_lock< std::mutex > lock(shell->m_attachedLock);
            if(shell->m_attached) {
                lock.unlock();
                shell->createWindow();
                glfwMakeContextCurrent(shell->m_window);
                shell->onRender();
                shell->events();
                glfwPollEvents();
                glfwSwapBuffers(shell->m_window);
                if(glfwWindowShouldClose(shell->m_window)) shell->detach();
            }
            shellLock.lock();
        }
        std::scoped_lock< std::mutex > shellCountLock(nautilus::shellCountLock);
        if(nautilus::shellCount == 0) this->exit();
        exitLock.lock();
    }
    glfwTerminate();
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::exit() {
    std::scoped_lock< std::mutex > exitLock(nautilus::exitLock);
    nautilus::exit = true;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::terminate() {
    m_t0->join();
    return NAUTILUS_STATUS_OK;
}

NautilusCore::~NautilusCore() {
    std::unique_lock< std::mutex > exitMutex(nautilus::exitLock);
    nautilus::exit = true;
    exitMutex.unlock();
    std::scoped_lock< std::mutex > lock(nautilus::threadpoolLock);
    for(std::thread* t : nautilus::threadpool) t->join();
    for(std::thread* t : nautilus::threadpool) delete t;
}

#endif      // NAUTILUS_CORE_CPP