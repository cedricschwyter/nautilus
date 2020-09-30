#include <nautilus/Nautilus.hpp>

#include "RubiksShell.hpp"


/**
 * Main entry point for the application
 */ 
int main() {
    nautilus::NautilusShell* shell = new rubiks::RubiksShell();
    nautilus::NautilusPipeline* pipe = new nautilus::NautilusPipeline("default_3d_pipe");
    pipe->vertex("res/shaders/opengl/v330_core/standard_3d/standard_3d.glsl.vert");
    pipe->fragment("res/shaders/opengl/v330_core/standard_3d/standard_3d.glsl.frag");
    nautilus::NautilusCore::attach(shell);
    shell->attach(pipe);
    return 0;
}
