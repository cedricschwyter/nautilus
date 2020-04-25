#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    nautilus::NautilusShell* shell = new nautilus::NautilusShellOpenGL();
    shell->setShellContext(nautilus::NAUTILUS_SHELL_CONTEXT_WINDOWED);
    shell->setShellExtent(1280, 720);
    nautilus::NautilusCore::attach(shell);
    nautilus::NautilusCore::terminate();
    return 0;
}