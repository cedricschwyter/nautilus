#include <nautilus/Nautilus.hpp>

#include "DevShell.hpp"

#include <iostream>

namespace dev {

    NautilusShell*  shell;

    /**
     * Initializes everything
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus run(void) {
        shell = new DevShell();
        shell->setShellContext(NAUTILUS_SHELL_CONTEXT_WINDOWED);
        shell->setShellTitle("Dev Example 1");
        shell->setShellExtent(1280, 720);
        shell->setShellIcon("res/images/icons/nautilus.png");
        NautilusCore::setEnableVulkanValidationLayers();
        NautilusCore::attachShell(shell);
        return NAUTILUS_STATUS_OK;
    }

    /**
     * Cleans allocated resources
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus clean(void) {
        NautilusCore::terminate();
        delete dev::shell;
        return NAUTILUS_STATUS_OK;
    }

}

/**
 * Main entry point for the application
 */
int main() {
    dev::run();
    dev::clean();
    return NAUTILUS_STATUS_OK;
}