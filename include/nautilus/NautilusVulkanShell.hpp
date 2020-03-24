#ifndef NAUTILUS_VULKAN_SHELL_HPP
#define NAUTILUS_VULKAN_SHELL_HPP

#include "NautilusShell.hpp"
#include "NautilusNS.hpp"
#include "NautilusAssert.hpp"

#include <vector>
#include <string.h>

class NautilusVulkanShell : 
    public NautilusShell {
    using NautilusShell::NautilusShell;
public:    

    /**
     * Gets executed when the shell gets attached to the core
     */
    virtual void onAttach(void);

    /**
     * Gets executed at the specified frequency by the application loop
     * Computes rendering operations
     */ 
    virtual void onRender(void);

    /**
     * Creates a Vulkan-capable GLFW-window
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus createWindow(void);

    /**
     * Initializes the Vulkan API
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus initAPI(void);

protected:

private:

};

#endif      // NAUTILUS_VULKAN_SHELL_HPP