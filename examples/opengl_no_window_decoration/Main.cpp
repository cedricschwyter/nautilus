#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    nautilus::NautilusShell* shell = new nautilus::NautilusShellOpenGL();
    shell->setShellDecoration(false);
    nautilus::NautilusCore::attach(shell);
    return 0;
}