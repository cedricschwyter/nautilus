#ifndef DEV_SHELL_CPP
#define DEV_SHELL_CPP

#include "DevShell.hpp"

#include <iostream>

NautilusStatus DevShell::onAttach() {
    std::cout << "Hello from shell!" << std::endl;
    return NAUTILUS_OK;
}

#endif      // DEV_SHELL_CPP