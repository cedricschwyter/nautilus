#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    nautilus::NautilusShell* shell = new nautilus::NautilusShellVulkan();
    shell->setShellDecoration(false);
    nautilus::NautilusCore::attach(shell);
    nautilus::NautilusCore::terminate();
    delete shell;
    return 0;
}