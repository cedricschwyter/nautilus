#ifndef NAUTILUS_SHELL_DISPATCHER_CPP
#define NAUTILUS_SHELL_DISPATCHER_CPP

#include "NautilusShellDispatcher.hpp"

namespace nautilus {

    namespace dispatcher {

        void onDetach(GLFWwindow* _window) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->onDetach(_window);
        }

        void onResize(GLFWwindow* _window, int _w, int _h) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->onResize(_window, _w, _h);
        }

        void onFocus(GLFWwindow* _window, int _focus) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->onFocus(_window, _focus);
        }

        void onIconify(GLFWwindow* _window, int _iconify) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->onIconify(_window, _iconify);
        }

        void onCursor(GLFWwindow* _window, double _x, double _y) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->onCursor(_window, _x, _y);
        }

        void onCursorIn(GLFWwindow* _window, int _enter) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->onCursorIn(_window, _enter);
        }

        void onKey(
            GLFWwindow*     _window, 
            int             _key, 
            int             _scancode, 
            int             _action, 
            int             _mods) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->onKey(
                _window,
                _key, 
                _scancode, 
                _action, 
                _mods);
        }

        void onScroll(GLFWwindow* _window, double _dx, double _dy) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->onScroll(_window, _dx, _dy);
        }

    }

}

#endif      // NAUTILUS_SHELL_DISPATCHER_CPP