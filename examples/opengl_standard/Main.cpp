#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    NautilusShell* shell = new NautilusShellOpenGL();
    NautilusCore::attach(shell);
    NautilusCore::terminate();
    delete shell;
    return 0;
}