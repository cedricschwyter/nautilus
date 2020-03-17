#include <Nautilus.hpp>

#include "DevShell.hpp"

#include <iostream>

namespace dev {

    NautilusCore*   core;
    NautilusShell*  shell;
    NautilusShell*  otherShell;

    /**
     * Initializes everything
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus init(void) {
        core = new NautilusCore();
        shell = new DevShell();
        otherShell = new DevShell();
        shell->setShellContext(NAUTILUS_SHELL_CONTEXT_WINDOWED);
        shell->setShellTitle("Dev Example");
        shell->setShellExtent(1280, 720);
        shell->setShellIcon("res/images/icons/nautilus.png");
        core->attachShell(shell);

        otherShell->setShellContext(NAUTILUS_SHELL_CONTEXT_WINDOWED);
        otherShell->setShellTitle("Dev Example");
        otherShell->setShellExtent(1280, 720);
        otherShell->setShellIcon("res/images/icons/nautilus.png");
        core->attachShell(otherShell);
        return NAUTILUS_STATUS_OK;
    }

    /**
     * Cleans allocated resources
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus clean(void) {
        core->terminate();
        delete dev::shell;
        delete dev::core;
        return NAUTILUS_STATUS_OK;
    }

}

/**
 * Main entry point for the application
 */
int main() {
    dev::init();
    dev::clean();
    return NAUTILUS_STATUS_OK;
}