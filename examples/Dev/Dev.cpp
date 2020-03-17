#include <Nautilus.hpp>

#include "DevShell.hpp"

#include <iostream>

namespace dev {

    NautilusCore*   core;
    NautilusShell*  shell;
    NautilusShell*  otherShell;
    NautilusShell*  thirdShell;

    /**
     * Initializes everything
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus init(void) {
        core = new NautilusCore();
        shell = new DevShell();
        otherShell = new DevShell();
        thirdShell = new DevShell();

        shell->setShellContext(NAUTILUS_SHELL_CONTEXT_WINDOWED);
        shell->setShellTitle("Dev Example 1");
        shell->setShellExtent(1280, 720);
        shell->setShellIcon("res/images/icons/nautilus.png");
        core->attachShell(shell);

        otherShell->setShellContext(NAUTILUS_SHELL_CONTEXT_WINDOWED);
        otherShell->setShellTitle("Dev Example 2");
        otherShell->setShellExtent(720, 480);
        otherShell->setShellIcon("res/images/icons/nautilus.png");
        core->attachShell(otherShell);

        thirdShell->setShellContext(NAUTILUS_SHELL_CONTEXT_WINDOWED);
        thirdShell->setShellTitle("Dev Example 3");
        thirdShell->setShellExtent(480, 720);
        thirdShell->setShellIcon("res/images/icons/nautilus.png");
        core->attachShell(thirdShell);
        return NAUTILUS_STATUS_OK;
    }

    /**
     * Cleans allocated resources
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus clean(void) {
        core->terminate();
        delete dev::shell;
        delete dev::otherShell;
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