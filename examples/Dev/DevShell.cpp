#ifndef DEV_SHELL_CPP
#define DEV_SHELL_CPP

#include "DevShell.hpp"

#include <iostream>

NautilusStatus DevShell::onAttach() {
    return NAUTILUS_STATUS_OK;
}

NautilusStatus DevShell::onRender() {
    return NAUTILUS_STATUS_OK;
}

#endif      // DEV_SHELL_CPP