#ifndef NAUTILUS_NS_HPP
#define NAUTILUS_NS_HPP

#include <GLFW/glfw3.h>

#include "Nautilus.hpp"

#include <string>
#include <vector>

namespace nautilus {

    extern uint32_t FPS;
    extern bool exit;
    extern std::vector< NautilusShell* > shells;

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