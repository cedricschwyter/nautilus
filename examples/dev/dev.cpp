#include <Nautilus.hpp>

#include "DevShell.hpp"

#include <iostream>

namespace dev {

    NautilusCore*   core;
    NautilusShell*  shell;

    /**
     * Initializes everything
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus init(void) {
        core = new NautilusCore();
        shell = new DevShell();
        core->attachShell(shell);
        return NAUTILUS_OK;
    } 

}

/**
 * Main entry point for the application
 */
int main() {
    return dev::init();
}