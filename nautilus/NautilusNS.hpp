#ifndef NAUTILUS_NS_HPP
#define NAUTILUS_NS_HPP

#include <GLFW/glfw3.h>

#include "Nautilus.hpp"
#include "NautilusInterface.hpp"

#include <string>

namespace nautilus {

    /**
     * Sets the nautilus graphics interface
     * @param _interface The NautilusInterface to utilize
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus nautilusSetInterface(NautilusInterface _interface);

    /**
     * Initializes the GLFW library
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus initializeGLFW(void);

    /**
     * Creates a GLFW window and returns a pointer to the handle of it
     * @param _w The integer width of the window
     * @param _h The integer height of the window
     * @param _title The title of the window
     * @param _icon The icon of the window
     * @return Returns a pointer to a GLFWwindow
     */
    GLFWwindow* createGLFWwindow(uint32_t _w, uint32_t _h, std::string _title, unsigned char* _icon);

    /**
     * Defines a wrapper function to load an image using stb_image.h, 
     * because said file can only be included in *one* .cpp-source file
     * @param _path The path to the image on disk
     * @param _x The width of the image
     * @param _y The height of the image
     * @param _comp Something with channels and stuff - just put 0
     * @param _req_comp The amount of channels :
     *      STBI_default    = 0, // only used for desired_channels
     *      STBI_grey       = 1,
     *      STBI_grey_alpha = 2,
     *      STBI_rgb        = 3,
     *      STBI_rgb_alpha  = 4
     * @return Returns a as a unsigned char* reinterpreted pointer to a stbi_uc struct
     */
    unsigned char* loadSTBI(
        std::string _path, 
        int*        _x, 
        int*        _y, 
        int*        _comp, 
        int         _req_comp);

    /**
     * Defines a wrapper function to free a loaded image using stb_image.h, 
     * because said file can only be included in *one* .cpp-source file
     * @param _pixels The array of pixels as an unsigned char pointer
     * @return Returns a NautilusStatus status code
     */
    NautilusStatus freeSTBI(unsigned char* _pixels);

}

#endif      // NAUTILUS_NS_HPP