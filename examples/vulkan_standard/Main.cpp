#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    NautilusCore*   core  = new NautilusCore();
    NautilusShell*  shell = new NautilusVulkanShell();
    core->attachShell(shell);
    core->terminate();
    return 0;
}