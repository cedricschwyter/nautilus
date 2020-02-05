#ifndef NAUTILUS_SHELL_HPP
#define NAUTILUS_SHELL_HPP

#include "NautilusStatus.hpp"

class NautilusShell {
public:

    /**
     * Default constructor
     */
    NautilusShell(void);

    /**
     * Gets executed when the shell gets attached to the core
     * Must be overridden by derived class
     * @return Returns a NautilusStatus status code
     */
    virtual NautilusStatus onAttach(void) = 0;

    /**
     * Default destructor
     */ 
    ~NautilusShell(void);

};

#endif      // NAUTILUS_SHELL_hPP