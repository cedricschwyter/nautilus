#ifndef NAUTILUS_VULKAN_SHELL_HPP
#define NAUTILUS_VULKAN_SHELL_HPP

#include "NautilusShell.hpp"
#include "NautilusNS.hpp"
#include "NautilusAssert.hpp"
#include "NautilusVulkanQueueFamily.hpp"
#include "NautilusVulkanSwapchainDetails.hpp"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string.h>
#include <set>

class NautilusVulkanShell : 
    public NautilusShell {
    using NautilusShell::NautilusShell;
public:    

    /**
     * Gets executed when the shell gets attached to the core
     */
    virtual void onAttach(void);

    /**
     * Gets executed at the specified frequency by the application loop
     * Computes rendering operations
     */ 
    virtual void onRender(void);

    /**
     * Sets the default window hints for the corresponding API
     * @return Returns a NautilusStatus status code
     */ 
    virtual NautilusStatus setDefaultWindowHints(void);

    /**
     * Initializes the Vulkan API
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus initAPI(void);

protected:

    VkSurfaceKHR        m_surface               = VK_NULL_HANDLE;
    VkPhysicalDevice    m_physicalDevice        = VK_NULL_HANDLE;

private:

    /**
     * Creates a GLFWsurface for the GLFWwindow
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus createSurfaceGLFW(void);

    /**
     * Selects the most suitable physical device for computation
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus selectBestPhysicalDevice(void);

    /**
     * Evaluates how useful a physical device is
     * @param _device The physical device to rate
     * @return Returns an unsigned integer, the higher the better
     */ 
    uint32_t evaluateDeviceSuitabilityScore(VkPhysicalDevice _device);

    /**
     * Prints information about a physical GPU
     * @param _device The physical device
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus printPhysicalDevicePropertiesAndFeatures(VkPhysicalDevice _device);

    /**
     * Checks whether a physical device has support for the swapchain extension
     * @param _device The physical device to check
     * @return Returns true if it has support, false otherwise
     */ 
    bool checkDeviceSwapchainExtensionSupport(VkPhysicalDevice _device);

    /**
     * Enumerates the maximum Vulkan multisampling sample count
     * @return Returns the maximum Vulkan multisampling sample count in Vulkan VkSampleCountFlagBits format
     */ 
    VkSampleCountFlagBits enumerateMaximumMultisamplingSampleCount(void);

    /**
     * Finds suitable queue family indices on a physical device
     * @param _device The physical device to check
     * @return Returns a NautilusVulkanQueueFamily structure containing all necessary indices
     */ 
    NautilusVulkanQueueFamily findSuitableQueueFamily(VkPhysicalDevice _device);

    /**
     * Enumerates a physical devices swapchain details
     * @param _device The physical device to check
     * @return Returns a NautilusVulkanSwapchainDetails structure containing all necessary Vulkan information
     */ 
    NautilusVulkanSwapchainDetails querySwapchainDetails(VkPhysicalDevice _device);

};

#endif      // NAUTILUS_VULKAN_SHELL_HPP