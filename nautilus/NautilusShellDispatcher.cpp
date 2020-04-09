#ifndef NAUTILUS_SHELL_DISPATCHER_CPP
#define NAUTILUS_SHELL_DISPATCHER_CPP

#include "NautilusShellDispatcher.hpp"

namespace nautilus {

    namespace dispatcher {

        void resize(GLFWwindow* _window, int _w, int _h) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->resize(_window, _w, _h);
        }

        void focus(GLFWwindow* _window, int _focus) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->focus(_window, _focus);
        }

        void iconify(GLFWwindow* _window, int _iconify) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->iconify(_window, _iconify);
        }

        void cursor(GLFWwindow* _window, double _x, double _y) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->cursor(_window, _x, _y);
        }

        void cursorIn(GLFWwindow* _window, int _enter) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->cursorIn(_window, _enter);
        }

        void key(
            GLFWwindow*     _window, 
            int             _key, 
            int             _scancode, 
            int             _action, 
            int             _mods) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->key(
                _window,
                _key, 
                _scancode, 
                _action, 
                _mods);
        }

        void mouseScroll(GLFWwindow* _window, double _dx, double _dy) {
            NautilusShell* context = reinterpret_cast< NautilusShell* >(glfwGetWindowUserPointer(_window));
            context->mouseScroll(_window, _dx, _dy);
        }

    }

}

#endif      // NAUTILUS_SHELL_DISPATCHER_CPP