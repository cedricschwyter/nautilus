#ifndef EXAMPLE_SHELL_HPP
#define EXAMPLE_SHELL_HPP

#include <nautilus/Nautilus.hpp>

class ExampleShell 
    : public NautilusShellOpenGL {
    using NautilusShellOpenGL::NautilusShellOpenGL;
public:

    /**
     * Gets executed when the shell is attached to the core
     * @return Returns a NautilusStatus status code
     */
    void onAttach(void); 

    /**
     * Gets executed at the specified frequency to compute rendering operations
     * @return Returns a NautilusStatus status code
     */
    void onRender(void);

};

#endif      // EXAMPLE_SHELL_HPP