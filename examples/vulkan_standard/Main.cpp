#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    nautilus::NautilusShell* shell = new nautilus::NautilusShellVulkan();
    nautilus::NautilusCore::attach(shell);
    nautilus::NautilusCore::terminate();
    return 0;
}