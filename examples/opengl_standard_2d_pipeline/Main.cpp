#include <nautilus/Nautilus.hpp>

#include "ExampleShell.hpp"

/**
 * Main entry point for the application
 */
int main() {
    nautilus::NautilusShell* shell = new ExampleShell();
    nautilus::NautilusPipeline* pipe = new nautilus::NautilusPipeline("default_2d_pipe");
    pipe->vertex("res/shaders/opengl/v330_core/standard_2d/standard_2d.glsl.vert");
    pipe->fragment("res/shaders/opengl/v330_core/standard_2d/standard_2d.glsl.frag");
    shell->attach(pipe);
    nautilus::NautilusCore::attach(shell);
    return 0;
}
