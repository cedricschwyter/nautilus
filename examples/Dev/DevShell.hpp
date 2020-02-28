#ifndef DEV_SHELL_HPP
#define DEV_SHELL_HPP

#include <Nautilus.hpp>

class DevShell 
    : public NautilusOpenGLShell {
    using NautilusOpenGLShell::NautilusOpenGLShell;
public:

    /**
     * Gets executed when the shell is attached to the core
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus onAttach(void); 

    /**
     * Gets executed at the specified frequency to compute rendering operations
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus onRender(void);

};

#endif      // DEV_SHELL_HPP