#ifndef DEV_SHELL_HPP
#define DEV_SHELL_HPP

#include <Nautilus.hpp>

class DevShell 
    : public NautilusShell {
    using NautilusShell::NautilusShell;
public:

    /**
     * Gets executed when the shell is attached to the core
     */
    NautilusStatus onAttach(void); 

};

#endif      // DEV_SHELL_HPP