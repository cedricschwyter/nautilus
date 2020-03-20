#ifndef NAUTILUS_SHELL_DISPATCHER_HPP
#define NAUTILUS_SHELL_DISPATCHER_HPP

#include "NautilusShell.hpp"

#include <GLFW/glfw3.h>

namespace nautilus {

    namespace dispatcher {

        /**
         * @note Dispatch method to call non-static function in a static way
         * Gets executed when the window is detached from the core
         * @param _window A pointer to the GLFWwindow
         */ 
        void onDetach(GLFWwindow* _window);

        /**
         * @note Dispatch method to call non-static function in a static way
         * Gets executed when the window is resized
         * @param _window A pointer to the GLFWwindow
         * @param _w The new window width
         * @param _h The new window height
         */ 
        void onResize(GLFWwindow* _window, int _w, int _h);

        /**
         * @note Dispatch method to call non-static function in a static way
         * Gets executed when the window is detached from the core
         * @param _window A pointer to the GLFWwindow
         * @param _focus GLFW_TRUE if focus given, GLFW_FALSE if focus lost
         */ 
        void onFocus(GLFWwindow* _window, int _focus);

        /**
         * @note Dispatch method to call non-static function in a static way
         * Gets executed when the window is iconified/minimized/restored
         * @param _window A pointer to the GLFWwindow
         * @param _iconify GLFW_TRUE if the window was iconified, GLFW_FALSE if it was restored
         */ 
        void onIconify(GLFWwindow* _window, int _iconify);

        /**
         * @note Dispatch method to call non-static function in a static way
         * Gets executed when the mouse cursor is moved within the window
         * @param _window A pointer to the GLFWwindow
         * @param _x The new x-coordinate relative to the left edge of the window
         * @param _y The new y-coordinate relative to the top edge of the window
         */ 
        void onCursor(GLFWwindow* _window, double _x, double _y);

        /**
         * @note Dispatch method to call non-static function in a static way
         * Gets executed when the cursor is moved inside the window
         * @param _window A pointer to the GLFWwindow
         * @param _enter GLFW_TRUE if the cursor has entered the window, GLFW_FALSE if it has left it
         */ 
        void onCursorIn(GLFWwindow* _window, int _enter);

        /**
         * @note Dispatch method to call non-static function in a static way
         * Gets executed when a key is pressed
         * @param _window A pointer to the GLFWwindow
         * @param _key The GLFW keycode
         * @param _scancode  The system scancode of the key
         * @param _action The action (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT)
         * @param _mods Bitfield describing width modifier keys were held down
         */ 
        void onKey(
            GLFWwindow*     _window, 
            int             _key, 
            int             _scancode, 
            int             _action, 
            int             _mods);

        /**
         * @note Dispatch method to call non-static function in a static way
         * Gets executed when the window is detached from the core
         * @param _window A pointer to the GLFWwindow
         * @param _dx The x-offset of the scroll wheel
         * @param _dy The y-offset of the scroll wheel
         */ 
        void onScroll(GLFWwindow* _window, double _dx, double _dy);

    }

}

#endif      // NAUTILUS_SHELL_DISPATCHER_HPP