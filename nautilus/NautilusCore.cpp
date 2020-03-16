#ifndef NAUTILUS_CORE_CPP
#define NAUTILUS_CORE_CPP

#include "NautilusCore.hpp"
#include "NautilusNS.hpp"

NautilusCore::NautilusCore() {

}

NautilusStatus NautilusCore::attachShell(NautilusShell* _shell) {
    static uint32_t id = 0;
    std::unique_lock< std::mutex > idLock(_shell->m_idLock);
    _shell->m_id = id;
    idLock.unlock();
    id++;
    std::unique_lock< std::mutex > shellLock(nautilus::shellsLock);
    nautilus::shells.push_back(_shell);
    shellLock.unlock();
    _shell->onAttach();
    std::unique_lock< std::mutex > lock(_shell->m_attachedMutex);
    _shell->m_attached = true;
    lock.unlock();
    start();
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::start() {
    if(!nautilus::running) {
        nautilus::running = true;
        m_t0 = new std::thread(&NautilusCore::loop, this);
        m_t0->join();
    }
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::loop() {
    glfwInit();
    while(!nautilus::exit && nautilus::running) {
        std::scoped_lock< std::mutex > shellLock(nautilus::shellsLock);
        std::cout << nautilus::shells.size() << std::endl;
        for(NautilusShell* shell : nautilus::shells) {
            std::scoped_lock< std::mutex > lock(shell->m_attachedMutex);
            if(shell->m_attached) {
                shell->createWindow();
                glfwMakeContextCurrent(shell->m_window);
                shell->events();
                shell->onRender();
                glfwSwapBuffers(shell->m_window);
                glfwPollEvents();
            }
        }
        std::scoped_lock< std::mutex > exitLock(nautilus::exitLock);
        if(nautilus::shells.size() == 0) nautilus::exit = true;
    }
    glfwTerminate();
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