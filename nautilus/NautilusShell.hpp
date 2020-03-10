#ifndef NAUTILUS_SHELL_HPP
#define NAUTILUS_SHELL_HPP

#include "NautilusStatus.hpp"
#include "NautilusShellContext.hpp"

#include <GLFW/glfw3.h>

#include <iostream>

class NautilusShell {
public:

    /**
     * Default constructor
     */
    NautilusShell(void);

    /**
     * Gets executed when the shell gets attached to the core
     * @note Must be overridden by derived class
     * @return Returns a NautilusStatus status code
     */
    virtual NautilusStatus onAttach(void) = 0;

    /**
     * Gets executed at the specified frequency by the application loop
     * Computes rendering operations
     * @note Must be overridden by derived class
     * @return Returns a NautilusStatus status code
     */ 
    virtual NautilusStatus onRender(void) = 0;

    /**
     * Sets the window context to fullscreen, borderless or windowed
     * @param _context The NautilusShellContext to set the shell to
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus setShellContext(NautilusShellContext _context);

    /**
     * Sets the shells title
     * @param _title The title of the window
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus setShellTitle(std::string _title);

    /**
     * Sets the shell window size
     * @param _width The width of the window
     * @param _height The height of the window
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus setShellExtent(uint32_t _width, uint32_t _height);

    /**
     * Sets the shells window icon
     * @param _path The path to the icon on disk
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus setShellIcon(std::string _path);

    /**
     * Default destructor
     */ 
    ~NautilusShell(void);

protected:

    GLFWwindow* m_window;
    NautilusShellContext m_shellContext;
    GLFWmonitor* m_monitor;
    std::string m_title;
    uint32_t m_width;
    uint32_t m_height;
    std::string m_shellIconPath;

    NautilusStatus createWindow(void);

};

#endif      // NAUTILUS_SHELL_hPP