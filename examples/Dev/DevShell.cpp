#ifndef DEV_SHELL_CPP
#define DEV_SHELL_CPP

#include "DevShell.hpp"

#include <iostream>

NautilusStatus DevShell::onAttach() {
    std::cout << "Hello from onAttach!" << std::endl;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus DevShell::onRender() {
    std::cout << "Hello from onRender!" << std::endl;
    return NAUTILUS_STATUS_OK;
}

#endif      // DEV_SHELL_CPP