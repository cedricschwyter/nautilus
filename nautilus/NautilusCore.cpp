#ifndef NAUTILUS_CORE_CPP
#define NAUTILUS_CORE_CPP

#include "NautilusCore.hpp"
#include "NautilusNS.hpp"

#include <thread>

NautilusCore::NautilusCore() {
    glfwInit();
    loop();
}

NautilusStatus NautilusCore::attachShell(NautilusShell* _shell) {
    nautilus::shells.push_back(_shell);
    _shell->createWindow();
    _shell->onAttach();
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusCore::loop() {
    std::thread t0 = std::thread([=] () {
        while(!nautilus::exit) {
            for(auto& shell : nautilus::shells) {
                glfwMakeContextCurrent(shell->m_window);
                shell->onRender();
                glfwPollEvents();
                glfwSwapBuffers(shell->m_window);
            }
        }
        glfwTerminate();
    });
    t0.detach();
    return NAUTILUS_STATUS_OK;
}

NautilusCore::~NautilusCore() {
    
}

#endif      // NAUTILUS_CORE_CPP