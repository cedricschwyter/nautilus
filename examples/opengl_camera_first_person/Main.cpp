#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    nautilus::NautilusShell* shell = new nautilus::NautilusShellOpenGL();
    shell->setShellContext(nautilus::NAUTILUS_SHELL_CONTEXT_BORDERLESS);
    nautilus::NautilusCore::attach(shell);
    shell->setShellTitle("First Person Camera Example");
    return 0;
}
