#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    NautilusShell* shell = new NautilusOpenGLShell();
    shell->setShellContext(nautilus::NAUTILUS_SHELL_CONTEXT_WINDOWED);
    shell->setShellExtent(1280, 720);
    NautilusCore::attachShell(shell);
    NautilusCore::terminate();
    delete shell;
    return 0;
}