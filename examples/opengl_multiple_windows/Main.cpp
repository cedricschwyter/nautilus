#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    nautilus::NautilusShell*  shell1 = new nautilus::NautilusShellOpenGL();
    nautilus::NautilusShell*  shell2 = new nautilus::NautilusShellOpenGL(); 
    shell2->setShellExtent(720, 450);
    nautilus::NautilusCore::attach(shell1);
    nautilus::NautilusCore::attach(shell2);
    shell1->setShellTitle("OpenGL Window 1");
    shell2->setShellTitle("OpenGL Window 2");
    return 0;
}
