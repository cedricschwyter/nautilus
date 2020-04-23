#ifndef NAUTILUS_CORE_CPP
#define NAUTILUS_CORE_CPP

#include "NautilusCore.hpp"
#include "NautilusNS.hpp"

nautilus::NautilusStatus NautilusCore::attach(NautilusShell* _shell) {
    return get().attachI(_shell);
}

nautilus::NautilusStatus NautilusCore::loop() {
    return get().loopI();
}

nautilus::NautilusStatus NautilusCore::exit() {
    return get().exitI();
}

nautilus::NautilusStatus NautilusCore::terminate() {
    return get().terminateI();
}

nautilus::NautilusStatus NautilusCore::setEnableVulkanValidationLayers() {
    return get().setEnableVulkanValidationLayersInternal();
}

NautilusCore::NautilusCore() {
}

NautilusCore& NautilusCore::get() {
    static NautilusCore s_instance;
    return s_instance;
}

nautilus::NautilusStatus NautilusCore::attachI(NautilusShell* _shell) {
    static int32_t id = 0;
    std::unique_lock< std::mutex > idLock(_shell->m_idLock);
    _shell->m_id = id;
    idLock.unlock();
    id++;
    nautilus::shellCount++;
    std::unique_lock< std::mutex > shellLock(nautilus::shellsLock);
    nautilus::shells.push_back(_shell);
    shellLock.unlock();
    if(!nautilus::running) {
        nautilus::running = true;
        m_t0 = std::async(std::launch::async, NautilusCore::loop);
    }
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCore::loopI() {
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
                glfwMakeContextCurrent(shell->m_window);
                if(shell->mustRender())
                    shell->render();
                glfwPollEvents();
                glfwSwapBuffers(shell->m_window);
                if(glfwWindowShouldClose(shell->m_window)) shell->detach();
            } else {
                lock.unlock();
                shell->attach();
            }
            shellLock.lock();
        }
        nautilus::logger::meta();
        std::scoped_lock< std::mutex > shellCountLock(nautilus::shellCountLock);
        if(nautilus::shellCount == 0) exit();
        exitLock.lock();
    }
    std::unique_lock< std::mutex > shellLock(nautilus::shellsLock);
    glfwTerminate();
    nautilus::logger::terminate();
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCore::exitI() {
    std::scoped_lock< std::mutex > exitLock(nautilus::exitLock);
    nautilus::exit = true;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCore::terminateI() {
    m_t0.wait();
    std::unique_lock< std::mutex > exitMutex(nautilus::exitLock);
    nautilus::exit = true;
    exitMutex.unlock();
    std::unique_lock< std::mutex > shellLock(nautilus::shellsLock);
    for(auto shell : nautilus::shells)
        delete shell;
    shellLock.unlock();
    std::scoped_lock< std::mutex > lock(nautilus::threadpoolLock);
    for(std::thread* t : nautilus::threadpool) t->join();
    for(std::thread* t : nautilus::threadpool) delete t;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCore::setEnableVulkanValidationLayersInternal() {
    nautilus::enableVulkanValidationLayers = true;
    return nautilus::NAUTILUS_STATUS_OK;
}

NautilusCore::~NautilusCore() {
}

#endif      // NAUTILUS_CORE_CPP