#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    nautilus::NautilusShell* shell = new nautilus::NautilusShellOpenGL();
    nautilus::NautilusCore::attach(shell);
    nautilus::NautilusCore::terminate();
    delete shell;
    return 0;
}