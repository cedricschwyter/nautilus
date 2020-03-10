#ifndef NAUTILUS_CORE_HPP
#define NAUTILUS_CORE_HPP

#include "NautilusStatus.hpp"
#include "NautilusShell.hpp"

#include <GLFW/glfw3.h>

class NautilusCore {
public:

    /**
     * Default constructor
     */
    NautilusCore(void);

    /**
     * Attaches a shell to the core
     * @param _shell A pointer to a derived shell object
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus attachShell(NautilusShell* _shell);

    /**
     * Contains the main loop of the application
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus loop(void);

    /**
     * Default destructor
     */ 
    ~NautilusCore(void);

private:

    NautilusShell* m_shell;

};

#endif      // NAUTILUS_CORE_HPP