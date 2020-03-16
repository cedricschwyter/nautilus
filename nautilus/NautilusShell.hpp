#ifndef NAUTILUS_SHELL_HPP
#define NAUTILUS_SHELL_HPP

#include "NautilusStatus.hpp"
#include "NautilusShellContext.hpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include <mutex>

class NautilusShell {
public:

    GLFWwindow*         m_window            = nullptr;
    bool                m_attached          = false;
    std::mutex          m_attachedMutex;
    bool                m_windowCreated     = false;
    uint32_t            m_id;
    std::mutex          m_idLock;

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
     * Creates the actual shell window
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus createWindow(void);

    /**
     * Handles per-shell events
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus events(void);

    /**
     * Detaches the shell from the core it is attached to
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus detach(void);

    /**
     * Default destructor
     */ 
    ~NautilusShell(void);

protected:

    NautilusShellContext    m_shellContext;
    GLFWmonitor*            m_monitor;
    std::string             m_title;
    uint32_t                m_width;
    uint32_t                m_height;
    std::string             m_shellIconPath;

};

#endif      // NAUTILUS_SHELL_hPP