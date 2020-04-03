#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    NautilusShell*  shell = new NautilusOpenGLShell();
    NautilusCore::attachShell(shell);
    NautilusCore::terminate();
    return 0;
}