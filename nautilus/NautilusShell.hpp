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
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus onAttach(void);

    /**
     * Default destructor
     */ 
    ~NautilusShell(void);

};

#endif      // NAUTILUS_SHELL_hPP