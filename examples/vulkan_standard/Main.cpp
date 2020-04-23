#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    NautilusShell*  shell = new NautilusShellVulkan();
    NautilusCore::attach(shell);
    NautilusCore::terminate();
    return 0;
}