#ifndef DEV_SHELL_CPP
#define DEV_SHELL_CPP

#include "DevShell.hpp"

#include <iostream>

void DevShell::onAttach() {
}

void DevShell::onRender() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

#endif      // DEV_SHELL_CPP