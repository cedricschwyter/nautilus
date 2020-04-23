#include <nautilus/Nautilus.hpp>

/**
 * Main entry point for the application
 */
int main() {
    NautilusShell* shell = new NautilusShellOpenGL();
    NautilusCore::attach(shell);
    NautilusPipeline* pipe = new NautilusPipeline("default_2d_pipe");
    pipe->vertex("res/shaders/opengl/v330_core/standard_2d/standard_2d.glsl.vert");
    pipe->fragment("res/shaders/opengl/v330_core/standard_2d/standard_2d.glsl.frag");
    shell->attach(pipe);
    return NautilusCore::terminate();
}