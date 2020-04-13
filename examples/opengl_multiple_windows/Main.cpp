#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    NautilusShell*  shell1 = new NautilusOpenGLShell();
    NautilusShell*  shell2 = new NautilusOpenGLShell(); 
    shell2->setShellExtent(720, 450);
    NautilusCore::attachShell(shell1);
    NautilusCore::attachShell(shell2);
    NautilusCore::terminate();
    delete shell1;
    delete shell2;
    return 0;
}