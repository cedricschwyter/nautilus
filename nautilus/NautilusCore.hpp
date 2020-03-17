#ifndef NAUTILUS_CORE_HPP
#define NAUTILUS_CORE_HPP

#include "NautilusStatus.hpp"
#include "NautilusShell.hpp"

#include <GLFW/glfw3.h>

#include <thread>
#include <mutex>

class NautilusCore {
public:
    
    std::thread* m_t0;

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
     * Exits the application and ends all processes owned by it
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus exit(void);

    /**
     * Terminates the application, must be called manually by user, 
     * otherwise program will exit before even starting the main loop.
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus terminate(void);

    /**
     * Default destructor
     */ 
    ~NautilusCore(void);

};

#endif      // NAUTILUS_CORE_HPP