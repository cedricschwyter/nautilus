#ifndef NAUTILUS_CORE_HPP
#define NAUTILUS_CORE_HPP

#include "NautilusStatus.hpp"
#include "NautilusShell.hpp"
#include "NautilusLogger.hpp"
#include "NautilusQueueFamilyVulkan.hpp"
#include "NautilusCoreHandlesVulkan.hpp"

#include <GLFW/glfw3.h>

#include <future>
#include <thread>
#include <mutex>

namespace nautilus {

    class NautilusCore {
    public:

        static NautilusCore& get(void);

        /**
         * Attaches a shell to the core
         * @param _shell A pointer to a derived shell object
         * @return Returns a NautilusStatus status code
         */
        static NautilusStatus attach(NautilusShell* _shell);

        /**
         * Detaches a shell from the core
         * @param _shell A pointer to a derived shell object
         * @return Returns a NautilusStatus status code
         */
        static NautilusStatus detach(NautilusShell* _shell);

        /**
         * Exits the application and ends all processes owned by it
         * @return Returns a NautilusStatus status code
         */ 
        static NautilusStatus loop(void);

        /**
         * Returns true if the application should exit
         * @return Returns true if the application should exit
         */ 
        static bool exit(void);

        /**
         * Terminates the application, must be called manually by user, 
         * otherwise program will exit before even starting the main loop.
         * @return Returns a NautilusStatus status code
         */ 
        static NautilusStatus terminate(void);

        /**
         * Increases the shell count
         * @return Returns a NautilusStatus status code
         */ 
        static NautilusStatus increaseShellCount(void);

        /**
         * Decreases the shell count
         * @return Returns a NautilusStatus status code
         */ 
        static NautilusStatus decreaseShellCount(void);

        /**
         * Returns true if OpenGL has been initialized
         * @return Returns true if OpenGL has been initialized
         */ 
        static bool openGLInitialized(void);

        /**
         * Sets the OpenGL initialized flag variable
         * @return Returns a NautilusStatus status code
         */ 
        static NautilusStatus setOpenGLInitialized(void);

        /**
         * Returns true if Vulkan has been initialized
         * @return Returns true if Vulkan has been initialized
         */ 
        static bool vulkanInitialized(void);

        /**
         * Locks a mutex to prevent multiple APIs from initializing at the same time
         * @return Returns a NautilusStatus status code
         */ 
        static NautilusStatus lockInitMutex(void);

        /**
         * Unlocks a mutex to prevent multiple APIs from initializing at the same time
         * @return Returns a NautilusStatus status code
         */ 
        static NautilusStatus unlockInitMutex(void);

        /**
         * Sets the Vulkan initialized flag variable
         * @return Returns a NautilusStatus status code
         */ 
        static NautilusStatus setVulkanInitialized(void);

        /**
         * Enables Vulkan validation layers if available
         * Only set in debug/development, do not set in release
         * or deployment/production as these are very performance-heavy
         * Sets validation layers for all NautilusShellVulkans
         * @return Returns a NautilusStatus status code
         */ 
        static NautilusStatus setEnableVulkanValidationLayers(void);
        
        /**
         * Creates the Vulkan instance object
         * @return Returns a NautilusStatus status code
         */ 
        static NautilusStatus createVulkanInstance(void);

        /**
         * Checks whether Vulkan validation layers are supported
         * @return Returns true if validation layers are supported, returns false otherwise
         */ 
        static bool vulkanValidationLayersSupported(void);

        /**
         * Queries for the required Vulkan extensions
         * @return Returns an array of const char*'s each representing one extensions
         */
        static std::vector< const char* > queryRequiredVulkanExtensions(void);

        /**
         * Creates the debug messenger for Vulkan validation layers
         * @return Returns a NautilusStatus status code
         */ 
        static NautilusStatus createVulkanDebugMessenger(void);

        /**
         * Creates the debug messenger
         * @param _instance The Vulkan instance handle
         * @param _pCreateInfo The create info structure
         * @param _pAllocator The allocator
         * @param _pDebugMessenger The debug messenger handle
         * @return Returns a VkResult status code
         */
        static VkResult createVulkanDebugUtilsMessenger(
            VkInstance                                      _instance,
            const VkDebugUtilsMessengerCreateInfoEXT*       _pCreateInfo,
            const VkAllocationCallbacks*                    _pAllocator,
            VkDebugUtilsMessengerEXT*                       _pDebugMessenger);

        /**
         * Destroys the debug messenger
         * @param _instance The Vulkan instance handle
         * @param _debugMessenger The actual messenger handle
         * @param _pAllocator The Vulkan allocator
         * @return Returns a NautilusStatus status code
         */ 
        static NautilusStatus destroyVulkanDebugUtilsMessenger(
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
        static NautilusQueueFamilyVulkan findSuitableVulkanQueueFamily(VkPhysicalDevice _device, VkSurfaceKHR _surface);
        static NautilusQueueFamilyVulkan findSuitableVulkanQueueFamily(const NautilusCoreHandlesVulkan& _handles);

        /**
         * Returns suitable memory type index
         * @param _handles The Vulkan core handles
         * @param _typeFilter The memory type filter for Vulkan GPU memory
         * @param _memoryPropertyFlags The memory properties
         * @return Returns either an valid (>0) index or a negative NautilusStatus status code
         */ 
        static uint32_t enumerateSuitableVulkanMemoryType(
            const NautilusCoreHandlesVulkan&    _handles, 
            const uint32_t&                     _typeFilter, 
            const VkMemoryPropertyFlags&        _memoryPropertyFlags);

        /**
         * Callback function for Vulkan debug messenger
         * @param _messageSeverity The severity bit of the message (aka error, warning, info...)
         * @param _messageType The Vulkan message type
         * @param _pCallbackData The message data
         * @param _pUserData The user data
         * @return Returns a VkBool32
         */ 
        static VKAPI_ATTR VkBool32 VKAPI_CALL vulkanValidationLayerDebugMessageCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT           _messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT                  _messageType,
            const VkDebugUtilsMessengerCallbackDataEXT*      _pCallbackData,
            void*                                            _pUserData);

        /**
         * Returns the Vulkan allocator
         * @return Returns the Vulkan allocatir
         */ 
        static VkAllocationCallbacks* vulkanAllocator(void);

        /**
         * Returns the Vulkan instance handle
         * @return Returns the Vulkan instance handle
         */ 
        static VkInstance vulkanInstance(void);

        /**
         * Returns true if Vulkan validation layers should be enabled
         * @return Returns true if Vulkan validation layers should be enabled
         */ 
        static bool enableVulkanValidationLayers(void);

        /**
         * Returns the Vulkan validation layer debug messenger
         * @return Returns the Vulkan validation layer debug messenger
         */ 
        static VkDebugUtilsMessengerEXT vulkanValidationLayerDebugMessenger(void);

        /**
         * Returns the Vulkan validation layers
         * @return Returns the Vulkan validation layers
         */ 
        static std::vector< const char* > const& vulkanValidationLayers(void);

        /**
         * Returns the required Vulkan extensions
         * @return Returns the required Vulkan extensions
         */ 
        static std::vector< const char* > const& vulkanRequiredExtensions(void);

    private:
        
        std::future< NautilusStatus >                   m_t0;
        std::vector< NautilusShell* >                   m_shells;
        std::mutex                                      m_shellsLock;
        uint32_t                                        m_shellCount                              = 0;
        std::mutex                                      m_shellCountLock;
        bool                                            m_exit                                    = false;
        std::mutex                                      m_exitLock;
        bool                                            m_running                                 = false;
        std::mutex                                      m_runningLock;
        VkInstance                                      m_vulkanInstance                          = VK_NULL_HANDLE;
        bool                                            m_vulkanInstanceCreated                   = false;
        std::mutex                                      m_vulkanInstanceCreatedLock;
        VkAllocationCallbacks*                          m_vulkanAllocator                         = nullptr;
        bool                                            m_enableVulkanValidationLayers            = false;
        const std::vector< const char* >                m_vulkanValidationLayers                  = {
            "VK_LAYER_KHRONOS_validation",
        };
        VkDebugUtilsMessengerEXT                        m_vulkanValidationLayerDebugMessenger     = VK_NULL_HANDLE;
        bool                                            m_vulkanDebugUtilsMessengerCreated        = false;
        std::mutex                                      m_vulkanDebugUtilsMessengerCreatedLock;
        const std::vector< const char* >                m_vulkanRequiredExtensions                = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME 
        };
        bool                                            m_openGLInitialized                       = false;
        std::mutex                                      m_openGLInitializedMutex;
        bool                                            m_vulkanInitialized                       = false;
        std::mutex                                      m_vulkanInitializedMutex;
        std::mutex                                      m_initMutex;

        /**
         * Attaches a shell to the core
         * @param _shell A pointer to a derived shell object
         * @return Returns a NautilusStatus status code
         */
        NautilusStatus attachI(NautilusShell* _shell);

        /**
         * Detaches a shell from the core
         * @param _shell A pointer to a derived shell object
         * @return Returns a NautilusStatus status code
         */
        NautilusStatus detachI(NautilusShell* _shell);

        /**
         * Contains the main loop of the application
         * @return Returns a NautilusStatus status code
         */
        NautilusStatus loopI(void);

        /**
         * Returns true if the application should exit
         * @return Returns true if the application should exit
         */ 
        bool exitI(void);

        /**
         * Terminates the application, must be called manually by user, 
         * otherwise program will exit before even starting the main loop.
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus terminateI(void);

        /**
         * Increases the shell count
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus increaseShellCountI(void);

        /**
         * Decreases the shell count
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus decreaseShellCountI(void);

        /**
         * Returns true if OpenGL has been initialized
         * @return Returns true if OpenGL has been initialized
         */ 
        bool openGLInitializedI(void);

        /**
         * Sets the OpenGL initialized flag variable
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus setOpenGLInitializedI(void);

        /**
         * Returns true if Vulkan has been initialized
         * @return Returns true if Vulkan has been initialized
         */ 
        bool vulkanInitializedI(void);

        /**
         * Sets the Vulkan initialized flag variable
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus setVulkanInitializedI(void);

        /**
         * Locks a mutex to prevent multiple APIs from initializing at the same time
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus lockInitMutexI(void);

        /**
         * Unlocks a mutex to prevent multiple APIs from initializing at the same time
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus unlockInitMutexI(void);

        /**
         * Enables Vulkan validation layers if available
         * Only set in debug/development, do not set in release
         * or deployment/production as these are very performance-heavy
         * Sets validation layers for all NautilusShellVulkans
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus setEnableVulkanValidationLayersI(void);

        /**
         * Creates the Vulkan instance object
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus createVulkanInstanceI(void);

        /**
         * Returns true if Vulkan validation layers should be enabled
         * @return Returns true if Vulkan validation layers should be enabled
         */ 
        bool enableVulkanValidationLayersI(void);

        /**
         * Returns the Vulkan validation layer debug messenger
         * @return Returns the Vulkan validation layer debug messenger
         */ 
        VkDebugUtilsMessengerEXT vulkanValidationLayerDebugMessengerI(void);

        /**
         * Returns the Vulkan validation layers
         * @return Returns the Vulkan validation layers
         */ 
        std::vector< const char* > const& vulkanValidationLayersI(void);

        /**
         * Returns the required Vulkan extensions
         * @return Returns the required Vulkan extensions
         */ 
        std::vector< const char* > const& vulkanRequiredExtensionsI(void);

        /**
         * Checks whether Vulkan validation layers are supported
         * @return Returns true if validation layers are supported, returns false otherwise
         */ 
        bool vulkanValidationLayersSupportedI(void);

        /**
         * Queries for the required Vulkan extensions
         * @return Returns an array of const char*'s each representing one extensions
         */
        std::vector< const char* > queryRequiredVulkanExtensionsI(void);

        /**
         * Creates the debug messenger for Vulkan validation layers
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus createVulkanDebugMessengerI(void);

        /**
         * Creates the debug messenger
         * @param _instance The Vulkan instance handle
         * @param _pCreateInfo The create info structure
         * @param _pAllocator The allocator
         * @param _pDebugMessenger The debug messenger handle
         * @return Returns a VkResult status code
         */
        VkResult createVulkanDebugUtilsMessengerI(
            VkInstance                                      _instance,
            const VkDebugUtilsMessengerCreateInfoEXT*       _pCreateInfo,
            const VkAllocationCallbacks*                    _pAllocator,
            VkDebugUtilsMessengerEXT*                       _pDebugMessenger);

        /**
         * Destroys the debug messenger
         * @param _instance The Vulkan instance handle
         * @param _debugMessenger The actual messenger handle
         * @param _pAllocator The Vulkan allocator
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus destroyVulkanDebugUtilsMessengerI(
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
        NautilusQueueFamilyVulkan findSuitableVulkanQueueFamilyI(VkPhysicalDevice _device, VkSurfaceKHR _surface);
        NautilusQueueFamilyVulkan findSuitableVulkanQueueFamilyI(const NautilusCoreHandlesVulkan& _handles);

        /**
         * Returns suitable memory type index
         * @param _handles The Vulkan core handles
         * @param _typeFilter The memory type filter for Vulkan GPU memory
         * @param _memoryPropertyFlags The memory properties
         * @return Returns either an valid (>0) index or a negative NautilusStatus status code
         */ 
        uint32_t enumerateSuitableVulkanMemoryTypeI(
            const NautilusCoreHandlesVulkan&    _handles, 
            const uint32_t&                     _typeFilter, 
            const VkMemoryPropertyFlags&        _memoryPropertyFlags);

        /**
         * Callback function for Vulkan debug messenger
         * @param _messageSeverity The severity bit of the message (aka error, warning, info...)
         * @param _messageType The Vulkan message type
         * @param _pCallbackData The message data
         * @param _pUserData The user data
         * @return Returns a VkBool32
         */ 
        VKAPI_ATTR VkBool32 VKAPI_CALL vulkanValidationLayerDebugMessageCallbackI(
            VkDebugUtilsMessageSeverityFlagBitsEXT           _messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT                  _messageType,
            const VkDebugUtilsMessengerCallbackDataEXT*      _pCallbackData,
            void*                                            _pUserData);

        /**
         * Returns the Vulkan allocator
         * @return Returns the Vulkan allocatir
         */ 
        VkAllocationCallbacks* vulkanAllocatorI(void);

        /**
         * Returns the Vulkan instance handle
         * @return Returns the Vulkan instance handle
         */ 
        VkInstance vulkanInstanceI(void);

        /**
         * Default constructor
         */
        NautilusCore(void);

        /**
         * Default destructor
         */ 
        ~NautilusCore(void);

    };

}

#endif      // NAUTILUS_CORE_HPP