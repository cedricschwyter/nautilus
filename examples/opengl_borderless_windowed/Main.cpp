#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    NautilusShell* shell = new NautilusShellOpenGL();
    shell->setShellContext(nautilus::NAUTILUS_SHELL_CONTEXT_BORDERLESS);
    NautilusCore::attachShell(shell);
    NautilusCore::terminate();
    delete shell;
    return 0;
}