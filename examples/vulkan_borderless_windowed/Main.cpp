#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    nautilus::NautilusShell* shell = new nautilus::NautilusShellVulkan();
    shell->setShellContext(nautilus::NAUTILUS_SHELL_CONTEXT_BORDERLESS);
    nautilus::NautilusCore::attach(shell);
    return 0;
}