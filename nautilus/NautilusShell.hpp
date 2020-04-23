#ifndef NAUTILUS_SHELL_HPP
#define NAUTILUS_SHELL_HPP

#include "NautilusStatus.hpp"
#include "NautilusShellContext.hpp"
#include "NautilusShellDispatcher.hpp"
#include "NautilusAssert.hpp"
#include "NautilusPipeline.hpp"
#include "NautilusAPI.hpp"
#include "NautilusCamera.hpp"
#include "NautilusCameraFocus.hpp"
#include "NautilusCameraFPS.hpp"
#include "NautilusCamera2D.hpp"
#include "NautilusCameraMode.hpp"
#include "NautilusDimension.hpp"
#include "NautilusViewport.hpp"

#include <GLFW/glfw3.h>

#include <map>
#include <iostream>
#include <thread>
#include <future>
#include <condition_variable>
#include <algorithm>
#include <cstring>
#include <string>
#include <mutex>
#include <chrono>

class NautilusShell {
public:

    GLFWwindow*                 m_window            = nullptr;
    bool                        m_attached          = false;
    std::mutex                  m_attachedLock;
    std::condition_variable     m_attachedCond;
    uint32_t                    m_id;
    std::mutex                  m_idLock;
    bool                        m_callbacksSet      = false;
    bool                        m_defaultKeyBinds   = true;
    nautilus::NautilusAPI       m_api               = nautilus::NAUTILUS_API_UNSPECIFIED;;

    /**
     * Default constructor
     */
    NautilusShell(void);
    
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
     * Executes API-specific rendering routines
     * Must be implemented by derived API shell
     * @return Returns a NautilusStatus status code
     */ 
    virtual nautilus::NautilusStatus render(void) = 0;

    /**
     * Detaches the shell from the core it is attached to
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus detach(void);

    /**
     * Gets executed when the window is resized
     * @param _window A pointer to the GLFWwindow
     * @param _w The new window width
     * @param _h The new window height
     */ 
    virtual void resize(GLFWwindow* _window, int _w, int _h);

    /**
     * Gets executed when the window is detached from the core
     * @param _window A pointer to the GLFWwindow
     * @param _focus GLFW_TRUE if focus given, GLFW_FALSE if focus lost
     */ 
    virtual void focus(GLFWwindow* _window, int _focus);

    /**
     * Gets executed when the window is iconified/minimized/restored
     * @param _window A pointer to the GLFWwindow
     * @param _iconify GLFW_TRUE if the window was iconified, GLFW_FALSE if it was restored
     */ 
    virtual void iconify(GLFWwindow* _window, int _iconify);

    /**
     * Gets executed when the mouse cursor is moved within the window
     * @param _window A pointer to the GLFWwindow
     * @param _x The new x-coordinate relative to the left edge of the window
     * @param _y The new y-coordinate relative to the top edge of the window
     */ 
    virtual void cursor(GLFWwindow* _window, double _x, double _y);

    /**
     * Gets executed when the cursor is moved inside the window
     * @param _window A pointer to the GLFWwindow
     * @param _enter GLFW_TRUE if the cursor has entered the window, GLFW_FALSE if it has left it
     */ 
    virtual void cursorIn(GLFWwindow* _window, int _enter);

    /**
     * Gets executed when a key is pressed
     * @param _window A pointer to the GLFWwindow
     * @param _key The GLFW keycode
     * @param _scancode  The system scancode of the key
     * @param _action The action (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT)
     * @param _mods Bitfield describing width modifier keys were held down
     */ 
    virtual void key(
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
    virtual void scroll(GLFWwindow* _window, double _dx, double _dy);

    /*
     * Sets the camera mode for the shell
     * @param _mode The mode to set the camera to
     * @return Returns a NautilusStatus status code
     */ 
    virtual nautilus::NautilusStatus setShellCamera(const nautilus::NautilusCameraMode& _mode);

    /**
     * Sets the shell to 2D/3D mode
     * @param _dim The amount of dimensions
     * @return Returns a NautilusStatus status code
     */
    nautilus::NautilusStatus setShellDimension(const nautilus::NautilusDimension& _dim);

    /**
     * Sets the window context to fullscreen, borderless or windowed
     * @param _context The NautilusShellContext to set the shell to
     * @return Returns a NautilusStatus status code
     */
    nautilus::NautilusStatus setShellContext(nautilus::NautilusShellContext _context);

    /**
     * Sets the shells title
     * @param _title The title of the window
     * @return Returns a NautilusStatus status code
     */
    nautilus::NautilusStatus setShellTitle(std::string _title);

    /**
     * Sets the shell window size
     * @param _width The width of the window
     * @param _height The height of the window
     * @return Returns a NautilusStatus status code
     */
    nautilus::NautilusStatus setShellExtent(uint32_t _width, uint32_t _height);

    /**
     * Sets the shells window icon
     * @param _path The path to the icon on disk
     * @return Returns a NautilusStatus status code
     */
    nautilus::NautilusStatus setShellIcon(std::string _path);

    /**
     * Sets the viewport for the shell
     * @param _viewport The viewport extent data
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus setShellViewport(const nautilus::NautilusViewport& _viewport);

    /**
     * Updates the viewport dynamically
     * Must be implemented by derived API shell
     * @param _viewport The viewport extent data
     * @return Returns a NautilusStatus status code
     */ 
    virtual nautilus::NautilusStatus updateShellViewport(const nautilus::NautilusViewport& _viewport) = 0;

    /**
     * Attaches and initializes a pipeline
     * @param _pipe The pipeline to attach
     * @return Returns a NautilusStatus status code
     */
    nautilus::NautilusStatus attach(NautilusPipeline* _pipe); 

    /**
     * Creates the actual shell window
     * @return Returns a NautilusStatus status code
     */
    nautilus::NautilusStatus createWindow(void);

    /**
     * Sets the necessary callback pointers
     * @returns Returns a NautilusStatus status code
     */
    nautilus::NautilusStatus setCallbacks(void);

    /**
     * Sets the shells FPS
     * @param _fps The maximum FPS of the shell
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus setShellRefreshRate(uint32_t _fps);

    /**
     * Activates/deactivates the window decoration
     * Can only be set once on shell creation
     * @param _decoration Shell decoration true or false
     * @return Returns a NautilusStatus status code
     */
    nautilus::NautilusStatus setShellDecoration(bool _decoration = true); 

    /**
     * Returns true if the shell needs to refresh
     * @return Returns true if enough time has passed for the shell to refresh
     */ 
    bool mustRender(void);

    /**
     * Initializes the graphics API
     * Must be implemented by derived API shell
     * @return Returns a NautilusStatus status code
     */ 
    virtual nautilus::NautilusStatus initAPI(void) = 0;

    /**
     * Executes API-specific cleanup and garbage collection routines
     * Must be implemented by derived API shell
     * @return Returns a NautilusStatus status code
     */ 
    virtual nautilus::NautilusStatus clean(void) = 0;

    /**
     * Halts the current thread until the shell is attached to the application core
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus waitUntilAttachedToCore(void);

    /**
     * Activates a pipeline based on its identifier
     * @param _identifier The pipeline's identifier
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus activate(const std::string& _identifier);

    /**
     * Default destructor
     */ 
    ~NautilusShell(void);

protected:

    nautilus::NautilusShellContext                      m_shellContext      = nautilus::defaults::SHELL_CONTEXT;
    GLFWmonitor*                                        m_monitor;
    std::string                                         m_title             = nautilus::defaults::CONTEXT_NAME;
    uint32_t                                            m_width             = 1280;
    uint32_t                                            m_height            = 720;
    std::string                                         m_shellIconPath     = "res/images/icons/nautilus.png";
    bool                                                m_windowCreated     = false;
    bool                                                m_initializedAPI    = false;
    nautilus::NautilusDimension                         m_dim               = nautilus::defaults::SHELL_DIMENSION;
    nautilus::NautilusCameraMode                        m_cameraMode        = nautilus::defaults::SHELL_CAMERA_MODE;
    NautilusCamera*                                     m_camera;
    nautilus::NautilusViewport                          m_viewport;
    uint32_t                                            m_fps               = nautilus::defaults::SHELL_FPS;
    double                                              m_pastTime          = 0;
    float                                               m_nbFrames          = 0;
    float                                               m_maxfps            = 0;
    double                                              m_lastTime          = glfwGetTime();
    bool                                                m_decoration        = true;
    std::map< const std::string, NautilusPipeline* >    m_pipelines;

    /**
     * Prints FPS et al to the console
     * @return Returns a NautilusStatus status code
     */  
    nautilus::NautilusStatus printStats(void);

    /**
     * Sets the global default window hints
     * @return Returns a NautilusStatus status code
     */  
    nautilus::NautilusStatus setDefaultWindowHints(void);

    /**
     * Sets API specific window hints
     * @return Returns a NautilusStatus status code
     */ 
    virtual nautilus::NautilusStatus setAPIWindowHints(void) = 0;

    /**
     * Attaches and initializes the shell
     * @return Returns a NautilusStatus status code
     */
    nautilus::NautilusStatus attach(void); 

    friend class NautilusCore;

};

#endif      // NAUTILUS_SHELL_hPP