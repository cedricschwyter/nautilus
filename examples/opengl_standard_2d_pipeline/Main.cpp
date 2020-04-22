#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    NautilusShell* shell = new NautilusShellOpenGL();
    NautilusPipeline* pipe = new NautilusPipeline();
    pipe->vertex("res/shaders/opengl/standard_2d/standard_2d.glsl.vert");
    pipe->fragment("res/shaders/opengl/standard_2d/standard_2d.glsl.frag");
    shell->attach(pipe);
    NautilusCore::attachShell(shell);
    NautilusCore::terminate();
    delete pipe;
    delete shell;
    return 0;
}