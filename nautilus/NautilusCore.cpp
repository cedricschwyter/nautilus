#ifndef NAUTILUS_CORE_CPP
#define NAUTILUS_CORE_CPP

#include "NautilusCore.hpp"
#include "NautilusNS.hpp"

NautilusStatus NautilusCore::attachShell(NautilusShell* _shell) {
    return get().attachShellInternal(_shell);
}

NautilusStatus NautilusCore::loop() {
    return get().loopInternal();
}

NautilusStatus NautilusCore::exit() {
    return get().exitInternal();
}

NautilusStatus NautilusCore::terminate() {
    return get().terminateInternal();
}

NautilusStatus NautilusCore::setEnableVulkanValidationLayers() {
    return get().setEnableVulkanValidationLayersInternal();
}

NautilusCore::NautilusCore() {
}

NautilusCore& NautilusCore::get() {
    static NautilusCore s_instance;
    return s_instance;
}

NautilusStatus NautilusCore::attachShellInternal(NautilusShell* _shell) {
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
        m_t0 = new std::thread([] () {
            NautilusCore::loop();
        });
    }
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::loopInternal() {
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
        std::scoped_lock< std::mutex > shellCountLock(nautilus::shellCountLock);
        if(nautilus::shellCount == 0) this->exit();
        exitLock.lock();
    }
    std::unique_lock< std::mutex > shellLock(nautilus::shellsLock);
    glfwTerminate();
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::exitInternal() {
    std::scoped_lock< std::mutex > exitLock(nautilus::exitLock);
    nautilus::exit = true;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::terminateInternal() {
    m_t0->join();
    std::unique_lock< std::mutex > exitMutex(nautilus::exitLock);
    nautilus::exit = true;
    exitMutex.unlock();
    std::scoped_lock< std::mutex > lock(nautilus::threadpoolLock);
    for(std::thread* t : nautilus::threadpool) t->join();
    for(std::thread* t : nautilus::threadpool) delete t;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::setEnableVulkanValidationLayersInternal() {
    nautilus::enableVulkanValidationLayers = true;
    return NAUTILUS_STATUS_OK;
}

NautilusCore::~NautilusCore() {
}

#endif      // NAUTILUS_CORE_CPP