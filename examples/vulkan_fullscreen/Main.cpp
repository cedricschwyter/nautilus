#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    NautilusShell* shell = new NautilusShellVulkan();
    shell->setShellContext(nautilus::NAUTILUS_SHELL_CONTEXT_FULLSCREEN);
    NautilusCore::attach(shell);
    NautilusCore::terminate();
    delete shell;
    return 0;
}