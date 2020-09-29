#include <nautilus/Nautilus.hpp>


/**
 * Main entry point for the application
 */ 
int main() {
    nautilus::NautilusShell* shell = new nautilus::NautilusShellOpenGL();
    nautilus::NautilusPipeline* pipe = new nautilus::NautilusPipeline("default_3d_pipe");
    pipe->vertex("res/shaders/opengl/v330_core/standard_3d/standard_3d.glsl.vert");
    pipe->fragment("res/shaders/opengl/v330_core/standard_3d/standard_3d.glsl.frag");
    shell->attach(pipe);
    nautilus::NautilusCore::attach(shell);
    return 0;
}
