#ifndef NAUTILUS_UTIL_HPP
#define NAUTILUS_UTIL_HPP

#include "NautilusShell.hpp"
#include "NautilusLogger.hpp"
#include "NautilusQueueFamilyVulkan.hpp"
#include "NautilusQueueTypeVulkan.hpp"
#include "NautilusCoreHandlesVulkan.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <chrono>
#include <map>
#include <thread>
#include <mutex>

namespace nautilus {

    namespace util {

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
         * @param _container The vector containing the element
         * @param _element The element itself
         * @return Returns an std::pair of bool (element found in vector?) and its index if found
         */ 
        template< template< typename, typename > typename _Titer, typename _T >
        std::pair< bool, int32_t > getIndexOfElement(const _Titer< _T , std::allocator< _T > >& _container, const _T& _element);
        template< template< typename, typename > typename _Titer, typename _T >
        std::pair< bool, int32_t > getIndexOfElement(const _Titer< _T* , std::allocator< _T* > >& _container, const _T*& _element);

        /**
         * Starts to record a command buffer for a specified queue type
         * Must immediately after vkCmd* be terminated by 
         * endVulkanCommandBuffer(const VkCommandBuffer& _cmdBuf) 
         * You are going to run into multithreading issues on you GPU otherwie
         * @param _queue The type of queue to record command buffer for
         * @return Returns a handle to the VkCommandBuffer
         */
        VkCommandBuffer startVulkanCommandBuffer(const NautilusVulkanQueueType& _queue);

        /**
         * Ends the recording of a command buffer
         * @param _cmdBuf The command buffer to end
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus endVulkanCommandBuffer(const VkCommandBuffer& _cmdBuf);

        /**
         * Defines a hash function for a field of a type
         * @param _hash The previously computed hash
         * @param _field The field to include in the computed hash
         * @return Returns the new hash
         */ 
        template< typename _T >
        std::size_t hashField(std::size_t* _hash, const _T& _field);

        /*
        * Loads a file to a char buffer
        * @param _path The relative path to the file on disk
        * @return Returns an std::vector< char >
        */ 
        const std::vector< char > loadFile(const std::string& _path);

    }

}

#include "NautilusUtil.tcc"

#endif      // NAUTILUS_UTIL_HPP