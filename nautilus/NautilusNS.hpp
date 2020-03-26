#ifndef NAUTILUS_NS_HPP
#define NAUTILUS_NS_HPP

#include "Nautilus.hpp"

#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <chrono>
#include <map>
#include <thread>
#include <mutex>

namespace nautilus {

    extern uint32_t                                     FPS;
    extern bool                                         exit;
    extern std::mutex                                   exitLock;
    extern bool                                         running;
    extern std::mutex                                   runningLock;
    extern std::vector< NautilusShell* >                shells;
    extern std::mutex                                   shellsLock;
    extern std::vector< std::thread* >                  threadpool;
    extern std::mutex                                   threadpoolLock;
    extern uint32_t                                     shellCount;
    extern std::mutex                                   shellCountLock;


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

    /**
     * Finds the index of an element in a std::vector
     * @param _vec The vector containing the element
     * @param _element The element itself
     * @return Returns a std::pair of bool (element found in vector?) and its index if found
     */ 
    template< typename T>
    std::pair< bool, int32_t > getIndexOfElement(const std::vector< T >& _vec, const T& _element);

    /**
     * Finds the index of an element in a std::vector
     * @param _vec The vector containing the element
     * @param _element The element itself
     * @return Returns a std::pair of bool (element found in vector?) and its index if found
     */ 
    template< typename T >
    std::pair< bool, int32_t > getIndexOfElement(const std::vector< T* >& _vec, const T* _element);

}

#endif      // NAUTILUS_NS_HPP