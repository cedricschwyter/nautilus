#ifndef NAUTILUS_ASSERT_HPP
#define NAUTILUS_ASSERT_HPP

#include "NautilusStatus.hpp"

#include <vulkan/vulkan.h>

#include <iostream>
#include <string>

/**
 * Throws an exception when _status is negative
 * @param _status The status code to assert
 * @throw Throws an std::runtime_error when _status is negative 
 */ 
inline void ASSERT_NAUTILUS(NautilusStatus _status) {
    if(_status < 0) {
        throw std::runtime_error("Nautilus ran into a fatal problem: " + _status);
    }
}

/**
 * Throws an exception when _result is not 0
 * @param _result The Vulkan result code to assert
 * @throw Throws an std::runtime_error when _result is not 0
 */ 
inline void ASSERT_VULKAN(VkResult _result) {
    if(_result != 0) {
        throw std::runtime_error("Vulkan ran into a fatal problem: " + _result);
    }
}

#endif      // NAUTILUS_ASSERT_HPP