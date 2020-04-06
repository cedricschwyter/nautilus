#ifndef NAUTILUS_SHELL_CPP
#define NAUTILUS_SHELL_CPP

#include "NautilusShell.hpp"
#include "NautilusNS.hpp"

#include <iostream>

void NautilusShell::onDetach(GLFWwindow* _window) {
    nautilus::logger::log("onDetach");
}

void NautilusShell::onResize(GLFWwindow* _window, int _w, int _h) {
    nautilus::logger::log("onResize");
}

void NautilusShell::onFocus(GLFWwindow* _window, int _focus) {
    nautilus::logger::log("onFocus");
}

void NautilusShell::onIconify(GLFWwindow* _window, int _iconify) {
    nautilus::logger::log("onIconify");
}

void NautilusShell::onCursor(GLFWwindow* _window, double _x, double _y) {
    nautilus::logger::log("onCursor");
}

void NautilusShell::onCursorIn(GLFWwindow* _window, int _enter) {
    nautilus::logger::log("onCursorIn");
}

void NautilusShell::onKey(
    GLFWwindow*     _window, 
    int             _key, 
    int             _scancode, 
    int             _action, 
    int             _mods) {
    if(_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->m_window, GLFW_TRUE);
    }
}

void NautilusShell::onScroll(GLFWwindow* _window, double _dx, double _dy) {
    nautilus::logger::log("onScroll");
}

NautilusStatus NautilusShell::setShellContext(NautilusShellContext _context) {
    this->m_shellContext = _context;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::setShellTitle(std::string _title) {
    this->m_title = _title;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::setShellExtent(uint32_t _width, uint32_t _height) {
    this->m_width = _width;
    this->m_height = _height;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::setShellIcon(std::string _path) {
    this->m_shellIconPath = _path;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::attach() {
    this->createWindow();
    this->setCallbacks();
    this->onAttach();
    std::unique_lock< std::mutex > lock(this->m_attachedLock);
    this->m_attached = true;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::detach() {
    std::scoped_lock< std::mutex > lock(m_attachedLock);
    this->m_attached = false;
    delete this->m_camera;
    this->clean();
    this->onDetach(this->m_window);
    std::scoped_lock< std::mutex > shellCountLock(nautilus::shellCountLock);
    nautilus::shellCount--;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::setCallbacks() {
    if(this->m_callbacksSet) return NAUTILUS_STATUS_OK;
    glfwSetFramebufferSizeCallback(this->m_window, nautilus::dispatcher::onResize);
    glfwSetWindowFocusCallback(this->m_window, nautilus::dispatcher::onFocus);
    glfwSetWindowIconifyCallback(this->m_window, nautilus::dispatcher::onIconify);
    glfwSetCursorPosCallback(this->m_window, nautilus::dispatcher::onCursor);
    glfwSetCursorEnterCallback(this->m_window, nautilus::dispatcher::onCursorIn);
    glfwSetKeyCallback(this->m_window, nautilus::dispatcher::onKey);
    this->m_callbacksSet = true;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::createWindow() { 
    if(this->m_windowCreated) return NAUTILUS_STATUS_OK;
    nautilus::logger::log("Creating GLFWwindow...");
    this->setDefaultWindowHints();
    this->m_monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(this->m_monitor);
    if(this->m_shellContext == NAUTILUS_SHELL_CONTEXT_WINDOWED) {
        this->m_window = glfwCreateWindow(
            this->m_width,
            this->m_height,
            this->m_title.c_str(),
            nullptr,
            nullptr);
        glfwSetWindowPos(
            this->m_window,
            mode->width / 2 - this->m_width / 2,
            mode->height / 2 - this->m_height / 2);
    }
    else if(this->m_shellContext == NAUTILUS_SHELL_CONTEXT_FULLSCREEN) {
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        this->m_window = glfwCreateWindow(
            mode->width,
            mode->height,
            this->m_title.c_str(),
            this->m_monitor,
            nullptr);
    }
    else if(this->m_shellContext == NAUTILUS_SHELL_CONTEXT_BORDERLESS) {
        this->m_window = glfwCreateWindow(
            mode->width,
            mode->height,
            this->m_title.c_str(),
            this->m_monitor,
            nullptr);
    }
    if(this->m_window == nullptr) {
        nautilus::logger::log("Failed to create GLFWwindow", NAUTILUS_STATUS_FATAL);
        return NAUTILUS_STATUS_FATAL;
    }
    glfwMakeContextCurrent(this->m_window);
    GLFWimage windowIcon[1];
    windowIcon[0].pixels = nautilus::loadSTBI(
        this->m_shellIconPath,
        &windowIcon[0].width,
        &windowIcon[0].height,
        0,
        4);
    glfwSetWindowIcon(this->m_window, 1, windowIcon);
    nautilus::freeSTBI(windowIcon[0].pixels);
    glfwSetWindowUserPointer(this->m_window, this);
    nautilus::logger::log("Successfully created GLFWwindow");
    this->initAPI();
    this->m_windowCreated = true;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::setShellCamera(NautilusCameraMode _mode) {
    this->m_cameraMode = _mode;
    delete this->m_camera;
    switch(_mode) {
        case NAUTILUS_CAMERA_MODE_2D:
            this->m_dim = NAUTILUS_DIMENSION_2D;
            this->m_camera = new NautilusCamera2D();
            break;
        case NAUTILUS_CAMERA_MODE_FPS:
            this->m_dim = NAUTILUS_DIMENSION_3D;
            this->m_camera = new NautilusCameraFPS();
            break;
        case NAUTILUS_CAMERA_MODE_FOCUS:
            this->m_dim = NAUTILUS_DIMENSION_3D;
            this->m_camera = new NautilusCameraFocus();
            break;
        default:
            nautilus::logger::log("Unknown camera mode", NAUTILUS_STATUS_FATAL);
            break;
    }
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShell::setShellDimension(NautilusDimension _dim) {
    this->m_dim = _dim;
    return NAUTILUS_STATUS_OK;
}

#endif      // NAUTILUS_SHELL_CPP