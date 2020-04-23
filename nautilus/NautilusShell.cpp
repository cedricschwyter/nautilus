#ifndef NAUTILUS_SHELL_CPP
#define NAUTILUS_SHELL_CPP

#include "NautilusShell.hpp"
#include "NautilusCore.hpp"
#include "NautilusUtil.hpp"

#include <iostream>

namespace nautilus {

    NautilusShell::NautilusShell() {
        m_camera = new NautilusCamera2D();
    }

    NautilusShell::~NautilusShell() {
        delete m_camera;
        for(auto entry : m_pipelines)
            delete entry.second;
    }

    NautilusStatus NautilusShell::loop() {
        while(!NautilusCore::exit()) {
            std::unique_lock< std::mutex > lock(m_attachedLock);
            if(m_attached){
                lock.unlock();
                glfwMakeContextCurrent(m_window);
                if(mustRender())
                    render();
                glfwPollEvents();
                glfwSwapBuffers(m_window);
                if(glfwWindowShouldClose(m_window))
                    detach();
            } else {
                lock.unlock();
                attach();
            }
        }
        return NAUTILUS_STATUS_OK;
    }

    void NautilusShell::onDetach(GLFWwindow* _window) {
    }

    void NautilusShell::onResize(GLFWwindow* _window, int _w, int _h) {
    }

    void NautilusShell::onFocus(GLFWwindow* _window, int _focus) {
    }

    void NautilusShell::onIconify(GLFWwindow* _window, int _iconify) {
    }

    void NautilusShell::onCursor(GLFWwindow* _window, double _x, double _y) {
    }

    void NautilusShell::onCursorIn(GLFWwindow* _window, int _enter) {
    }

    void NautilusShell::onKey(
        GLFWwindow*     _window, 
        int             _key, 
        int             _scancode, 
        int             _action, 
        int             _mods) {
        if(_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS) {
            glfwSetWindowShouldClose(m_window, GLFW_TRUE);
        }
    }

    void NautilusShell::onScroll(GLFWwindow* _window, double _dx, double _dy) {
    }

    void NautilusShell::resize(GLFWwindow* _window, int _w, int _h) {
        onResize(_window, _w, _h);
    }

    void NautilusShell::focus(GLFWwindow* _window, int _focus) {
        onFocus(_window, _focus);
    }

    void NautilusShell::iconify(GLFWwindow* _window, int _iconify) {
        onIconify(_window, _iconify);
    }

    void NautilusShell::cursor(GLFWwindow* _window, double _x, double _y) {
        onCursor(_window, _x, _y);
        m_camera->cursor(_window, _x, _y);
    }

    void NautilusShell::cursorIn(GLFWwindow* _window, int _enter) {
        onCursorIn(_window, _enter);
    }

    void NautilusShell::key(
        GLFWwindow*     _window, 
        int             _key, 
        int             _scancode, 
        int             _action, 
        int             _mods) {
        onKey(
            _window,
            _key,
            _scancode,
            _action,
            _mods);
        m_camera->key(
            _window,
            _key,
            _scancode,
            _action,
            _mods);
    }

    void NautilusShell::scroll(GLFWwindow* _window, double _dx, double _dy) {
        onScroll(_window, _dx, _dy);
        m_camera->scroll(_window, _dx, _dy);
    }

    NautilusStatus NautilusShell::setShellContext(NautilusShellContext _context) {
        m_shellContext = _context;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::setShellTitle(std::string _title) {
        m_title = _title;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::setShellExtent(uint32_t _width, uint32_t _height) {
        m_width = _width;
        m_height = _height;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::setShellIcon(std::string _path) {
        m_shellIconPath = _path;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::attach() {
        createWindow();
        setCallbacks();
        std::unique_lock< std::mutex > lock(m_attachedLock);
        m_attached = true;
        m_attachedCond.notify_all();
        onAttach();
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::detach() {
        std::scoped_lock< std::mutex > lock(m_attachedLock);
        m_attached = false;
        delete m_camera;
        clean();
        onDetach(m_window);
        glfwDestroyWindow(m_window);
        NautilusCore::detach(this);
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::setCallbacks() {
        if(m_callbacksSet) return NAUTILUS_STATUS_OK;
        glfwSetFramebufferSizeCallback(m_window, dispatcher::resize);
        glfwSetWindowFocusCallback(m_window, dispatcher::focus);
        glfwSetWindowIconifyCallback(m_window, dispatcher::iconify);
        glfwSetCursorPosCallback(m_window, dispatcher::cursor);
        glfwSetCursorEnterCallback(m_window, dispatcher::cursorIn);
        glfwSetKeyCallback(m_window, dispatcher::key);
        m_callbacksSet = true;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::setDefaultWindowHints() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        if(!m_decoration) glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::createWindow() { 
        if(m_windowCreated) return NAUTILUS_STATUS_OK;
        logger::log("Creating GLFWwindow...");
        setDefaultWindowHints();
        setAPIWindowHints();
        m_monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
        if(m_shellContext == NAUTILUS_SHELL_CONTEXT_WINDOWED) {
            m_window = glfwCreateWindow(
                m_width,
                m_height,
                m_title.c_str(),
                nullptr,
                nullptr);
            glfwSetWindowPos(
                m_window,
                mode->width / 2 - m_width / 2,
                mode->height / 2 - m_height / 2);
        }
        else if(m_shellContext == NAUTILUS_SHELL_CONTEXT_FULLSCREEN) {
            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
            m_window = glfwCreateWindow(
                mode->width,
                mode->height,
                m_title.c_str(),
                m_monitor,
                nullptr);
        }
        else if(m_shellContext == NAUTILUS_SHELL_CONTEXT_BORDERLESS) {
            m_window = glfwCreateWindow(
                mode->width,
                mode->height,
                m_title.c_str(),
                m_monitor,
                nullptr);
        }
        if(m_window == nullptr) {
            logger::log("Failed to create GLFWwindow", NAUTILUS_STATUS_FATAL);
            return NAUTILUS_STATUS_FATAL;
        }
        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(0);
        GLFWimage windowIcon[1];
        windowIcon[0].pixels = util::loadSTBI(
            m_shellIconPath,
            &windowIcon[0].width,
            &windowIcon[0].height,
            0,
            4);
        glfwSetWindowIcon(m_window, 1, windowIcon);
        util::freeSTBI(windowIcon[0].pixels);
        glfwSetWindowUserPointer(m_window, this);
        logger::log("Successfully created GLFWwindow");
        initAPI();
        m_windowCreated = true;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::setShellCamera(const NautilusCameraMode& _mode) {
        m_cameraMode = _mode;
        delete m_camera;
        switch(_mode) {
            case NAUTILUS_CAMERA_MODE_2D:
                m_dim = NAUTILUS_DIMENSION_2D;
                m_camera = new NautilusCamera2D();
                break;
            case NAUTILUS_CAMERA_MODE_FPS:
                m_dim = NAUTILUS_DIMENSION_3D;
                m_camera = new NautilusCameraFPS();
                break;
            case NAUTILUS_CAMERA_MODE_FOCUS:
                m_dim = NAUTILUS_DIMENSION_3D;
                m_camera = new NautilusCameraFocus();
                break;
            default:
                logger::log("Unknown camera mode", NAUTILUS_STATUS_FATAL);
                break;
        }
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::setShellDimension(const NautilusDimension& _dim) {
        m_dim = _dim;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::setShellViewport(const NautilusViewport& _viewport) {
        m_viewport = _viewport;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::setShellRefreshRate(uint32_t _fps) {
        m_fps = _fps;
        return NAUTILUS_STATUS_OK;
    }

    bool NautilusShell::mustRender() {
        static auto start = std::chrono::system_clock::now();
        auto now = std::chrono::system_clock::now();
        std::chrono::duration< double > elapsed = now - start;
        return elapsed.count() >= 1 / m_fps;
    }

    NautilusStatus NautilusShell::printStats() {
        double              currentTime         = glfwGetTime();
        double              deltaTime           = currentTime - m_pastTime;
        m_pastTime = currentTime;
        m_nbFrames++;
        float seconds = 10.0f;
        if(currentTime - m_lastTime >= 1.0 && m_nbFrames > m_maxfps)
            m_maxfps = m_nbFrames;
        if(currentTime - m_lastTime >= seconds) {
            std::string fps                = "Average FPS (last " + std::to_string(seconds) + " seconds):    " + std::to_string(double(m_nbFrames / seconds));
            std::string frametime          = "Average Frametime (last " + std::to_string(seconds) + " seconds):    " + std::to_string(double((1000.0 * seconds) /m_nbFrames)) + " ms";
            std::string maxFPS             = "Max FPS:    " + std::to_string(double(m_maxfps / seconds));
            logger::log("Stats for '" + m_title + "':");
            logger::log(fps);
            logger::log(frametime);
            logger::log(maxFPS);
            m_nbFrames = 0;
            m_lastTime += seconds;
        }
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::setShellDecoration(bool _decoration) {
        m_decoration = _decoration;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::attach(NautilusPipeline* _pipe) {
        waitUntilAttachedToCore();
        glfwMakeContextCurrent(m_window);
        m_pipelines[_pipe->identifier()] = _pipe;
        _pipe->attach(m_api);
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::waitUntilAttachedToCore() {
        std::unique_lock< std::mutex > lock(m_attachedLock);
        m_attachedCond.wait(lock, [this] () { return m_attached; });
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShell::activate(const std::string& _identifier) {
        m_pipelines[_identifier]->activate(m_api);
        return NAUTILUS_STATUS_OK;
    }

}

#endif      // NAUTILUS_SHELL_CPP