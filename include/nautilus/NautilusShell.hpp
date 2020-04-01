#ifndef NAUTILUS_SHELL_HPP
#define NAUTILUS_SHELL_HPP

#include "NautilusStatus.hpp"
#include "NautilusShellContext.hpp"
#include "NautilusShellDispatcher.hpp"
#include "NautilusAssert.hpp"
#include "NautilusAPI.hpp"

#include <GLFW/glfw3.h>

#include <map>
#include <iostream>
#include <thread>
#include <mutex>

class NautilusShell {
public:

    GLFWwindow*         m_window            = nullptr;
    bool                m_attached          = false;
    std::mutex          m_attachedLock;
    uint32_t            m_id;
    std::mutex          m_idLock;
    bool                m_callbacksSet      = false;
    bool                m_defaultKeyBinds   = true;
    NautilusAPI         m_API               = NAUTILUS_API_UNSPECIFIED;;

    /**
     * Default constructor
     */
    NautilusShell(void) = default;

    /**
     * Gets executed when the shell gets attached to the core
     * @return Returns a NautilusStatus status code
     */
    virtual void onAttach(void) = 0;

    /**
     * Gets executed at the specified frequency by the application loop
     * Computes rendering operations
     * @return Returns a NautilusStatus status code
     */ 
    virtual void onRender(void) = 0;

    /**
     * Gets executed when the window is detached from the core
     * @param _window A pointer to the GLFWwindow
     */ 
    virtual void onDetach(GLFWwindow* _window);

    /**
     * Gets executed when the window is resized
     * @param _window A pointer to the GLFWwindow
     * @param _w The new window width
     * @param _h The new window height
     */ 
    virtual void onResize(GLFWwindow* _window, int _w, int _h);

    /**
     * Gets executed when the window is detached from the core
     * @param _window A pointer to the GLFWwindow
     * @param _focus GLFW_TRUE if focus given, GLFW_FALSE if focus lost
     */ 
    virtual void onFocus(GLFWwindow* _window, int _focus);

    /**
     * Gets executed when the window is iconified/minimized/restored
     * @param _window A pointer to the GLFWwindow
     * @param _iconify GLFW_TRUE if the window was iconified, GLFW_FALSE if it was restored
     */ 
    virtual void onIconify(GLFWwindow* _window, int _iconify);

    /**
     * Gets executed when the mouse cursor is moved within the window
     * @param _window A pointer to the GLFWwindow
     * @param _x The new x-coordinate relative to the left edge of the window
     * @param _y The new y-coordinate relative to the top edge of the window
     */ 
    virtual void onCursor(GLFWwindow* _window, double _x, double _y);

    /**
     * Gets executed when the cursor is moved inside the window
     * @param _window A pointer to the GLFWwindow
     * @param _enter GLFW_TRUE if the cursor has entered the window, GLFW_FALSE if it has left it
     */ 
    virtual void onCursorIn(GLFWwindow* _window, int _enter);

    /**
     * Gets executed when a key is pressed
     * @param _window A pointer to the GLFWwindow
     * @param _key The GLFW keycode
     * @param _scancode  The system scancode of the key
     * @param _action The action (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT)
     * @param _mods Bitfield describing width modifier keys were held down
     */ 
    virtual void onKey(
        GLFWwindow*     _window, 
        int             _key, 
        int             _scancode, 
        int             _action, 
        int             _mods);

    /**
     * Gets executed when the window is detached from the core
     * @param _window A pointer to the GLFWwindow
     * @param _dx The x-offset of the scroll wheel
     * @param _dy The y-offset of the scroll wheel
     */ 
    virtual void onScroll(GLFWwindow* _window, double _dx, double _dy);

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
     * Sets the default window hints for the corresponding API
     * @return Returns a NautilusStatus status code
     */ 
    virtual NautilusStatus setDefaultWindowHints(void) = 0;

    /**
     * Sets the necessary callback pointers
     * @returns Returns a NautilusStatus status code
     */
    NautilusStatus setCallbacks(void);

    /**
     * Initializes the graphics API
     * Must be implemented by derived API shell
     * @return Returns a NautilusStatus status code
     */ 
    virtual NautilusStatus initAPI(void) = 0;

    /**
     * Executes API-specific rendering routines
     * Must be implemented by derived API shell
     * @return Returns a NautilusStatus status code
     */ 
    virtual NautilusStatus render(void) = 0;

    /**
     * Executes API-specific cleanup and garbage collection routines
     * Must be implemented by derived API shell
     * @return Returns a NautilusStatus status code
     */ 
    virtual NautilusStatus clean(void) = 0;

    /**
     * Attaches and initializes the shell
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus attach(void); 

    /**
     * Detaches the shell from the core it is attached to
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus detach(void);

    /**
     * Default destructor
     */ 
    ~NautilusShell(void) = default;

protected:

    NautilusShellContext    m_shellContext      = NAUTILUS_SHELL_CONTEXT_WINDOWED;
    GLFWmonitor*            m_monitor;
    std::string             m_title             = "Nautilus by D3PSI";
    uint32_t                m_width             = 1280;
    uint32_t                m_height            = 720;
    std::string             m_shellIconPath     = "res/images/icons/nautilus.png";
    bool                    m_windowCreated     = false;
    bool                    m_initializedAPI    = false;

};

#endif      // NAUTILUS_SHELL_hPP