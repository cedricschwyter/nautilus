#ifndef NAUTILUS_NS_HPP
#define NAUTILUS_NS_HPP

#include "NautilusShell.hpp"
#include "NautilusLogger.hpp"
#include "NautilusVulkanQueueFamily.hpp"
#include "NautilusVulkanQueueType.hpp"
#include "NautilusVulkanCoreHandles.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <chrono>
#include <map>
#include <thread>
#include <mutex>

namespace nautilus {

    extern const std::string                    globalApplicationName;
    extern bool                                 exit;
    extern std::mutex                           exitLock;
    extern bool                                 running;
    extern std::mutex                           runningLock;
    extern std::vector< NautilusShell* >        shells;
    extern std::mutex                           shellsLock;
    extern std::vector< std::thread* >          threadpool;
    extern std::mutex                           threadpoolLock;
    extern uint32_t                             shellCount;
    extern std::mutex                           shellCountLock;
    extern VkInstance                           vulkanInstance;
    extern bool                                 vulkanInstanceCreated;
    extern VkAllocationCallbacks*               vulkanAllocator;
    extern bool                                 enableVulkanValidationLayers;
    extern const std::vector< const char* >     vulkanValidationLayers;
    extern VkDebugUtilsMessengerEXT             vulkanValidationLayerDebugMessenger;
    extern const std::vector< const char* >     vulkanRequiredExtensions;
    extern VkSampleCountFlagBits                maxVulkanMSAASampleCount;

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
     * @return Returns a nautilus::NautilusStatus status code
     */
    nautilus::NautilusStatus freeSTBI(unsigned char* _pixels);

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

    /**
     * Creates the Vulkan instance object
     * @return Returns a nautilus::NautilusStatus status code
     */ 
    nautilus::NautilusStatus createVulkanInstance(void);

    /**
     * Checks whether Vulkan validation layers are supported
     * @return Returns true if validation layers are supported, returns false otherwise
     */ 
    bool vulkanValidationLayersSupported(void);

    /**
     * Queries for the required Vulkan extensions
     * @return Returns an array of const char*'s each representing one extensions
     */
    std::vector< const char* > queryRequiredVulkanExtensions(void);

    /**
     * Creates the debug messenger for Vulkan validation layers
     * @return Returns a nautilus::NautilusStatus status code
     */ 
    nautilus::NautilusStatus createVulkanDebugMessenger(void);

    /**
     * Callback function for Vulkan debug messenger
     * @param _messageSeverity The severity bit of the message (aka error, warning, info...)
     * @param _messageType The Vulkan message type
     * @param _pCallbackData The message data
     * @param _pUserData The user data
     * @return Returns a VkBool32
     */ 
    VKAPI_ATTR VkBool32 VKAPI_CALL vulkanValidationLayerDebugMessageCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT           _messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT                  _messageType,
        const VkDebugUtilsMessengerCallbackDataEXT*      _pCallbackData,
        void*                                            _pUserData);

    /**
     * Creates the debug messenger
     * @param _instance The Vulkan instance handle
     * @param _pCreateInfo The create info structure
     * @param _pAllocator The allocator
     * @param _pDebugMessenger The debug messenger handle
     * @return Returns a VkResult status code
     */
    VkResult createVulkanDebugUtilsMessenger(
        VkInstance                                      _instance,
        const VkDebugUtilsMessengerCreateInfoEXT*       _pCreateInfo,
        const VkAllocationCallbacks*                    _pAllocator,
        VkDebugUtilsMessengerEXT*                       _pDebugMessenger);

    /**
     * Destroys the debug messenger
     * @param _instance The Vulkan instance handle
     * @param _debugMessenger The actual messenger handle
     * @param _pAllocator The Vulkan allocator
     * @return Returns a nautilus::NautilusStatus status code
     */ 
    nautilus::NautilusStatus destroyVulkanDebugUtilsMessenger(
        VkInstance                          _instance,
        VkDebugUtilsMessengerEXT            _debugMessenger,
        const VkAllocationCallbacks*        _pAllocator);

    /**
     * Finds suitable queue family indices on a physical device
     * @param _device The physical device to check
     * @param _surface The VkSurfaceKHR
     * @param _handles A structure containing all the important Vulkan handles
     * @return Returns a NautilusVulkanQueueFamily structure containing all necessary indices
     */ 
    nautilus::NautilusVulkanQueueFamily findSuitableVulkanQueueFamily(VkPhysicalDevice _device, VkSurfaceKHR _surface);
    nautilus::NautilusVulkanQueueFamily findSuitableVulkanQueueFamily(const NautilusVulkanCoreHandles& _handles);

    /**
     * Returns suitable memory type index
     * @param _handles The Vulkan core handles
     * @param _typeFilter The memory type filter for Vulkan GPU memory
     * @param _memoryPropertyFlags The memory properties
     * @return Returns either an valid (>0) index or a negative NautilusStatus status code
     */ 
    uint32_t enumerateSuitableVulkanMemoryType(
        const nautilus::NautilusVulkanCoreHandles&  _handles, 
        const uint32_t&                             _typeFilter, 
        const VkMemoryPropertyFlags&                _memoryPropertyFlags);

    /**
     * Starts to record a command buffer for a specified queue type
     * Must immediately after vkCmd* be terminated by 
     * nautilus::endVulkanCommandBuffer(const VkCommandBuffer& _cmdBuf) 
     * You are going to run into multithreading issues on you GPU otherwie
     * @param _queue The type of queue to record command buffer for
     * @return Returns a handle to the VkCommandBuffer
     */
    VkCommandBuffer startVulkanCommandBuffer(const nautilus::NautilusVulkanQueueType& _queue);

    /**
     * Ends the recording of a command buffer
     * @param _cmdBuf The command buffer to end
     * @return Returns a nautilus::NautilusStatus status code
     */ 
    NautilusStatus endVulkanCommandBuffer(const VkCommandBuffer& _cmdBuf);

}

#endif      // NAUTILUS_NS_HPP