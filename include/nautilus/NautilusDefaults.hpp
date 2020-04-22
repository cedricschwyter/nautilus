#ifndef NAUTILUS_DEFAULTS_HPP
#define NAUTILUS_DEFAULTS_HPP

#include "NautilusShellContext.hpp"
#include "NautilusDimension.hpp" 
#include "NautilusCameraMode.hpp"

#include <glm/glm.hpp>

#include <string>

namespace nautilus {

    namespace defaults {

        extern const std::string                        CONTEXT_NAME;
        extern const std::string                        CONTEXT_NAME_OPENGL;
        extern const std::string                        CONTEXT_NAME_VULKAN;

        extern const std::string                        LOG_DIR;
        extern const std::string                        RESOURCE_DIR;
        extern const std::string                        IMAGE_DIR;
        extern const std::string                        ICON_DIR;
        extern const std::string                        SHADER_DIR;
        extern const std::string                        SHADER_DIR_OPENGL;
        extern const std::string                        SHADER_DIR_VULKAN;

        extern const float                              CAMERA_SPEED;
        extern const float                              CAMERA_SENS;
        extern const float                              CAMERA_FOV;
        extern const float                              CAMERA_MIN_FOV;
        extern const float                              CAMERA_MAX_FOV;
        extern const float                              CAMERA_MIN_PITCH;
        extern const float                              CAMERA_MAX_PITCH;

        extern const glm::vec3                          WORLD_ORIGIN;
        extern const glm::vec3                          WORLD_UP_OPENGL;
        extern const glm::vec3                          WORLD_UP_VULKAN;
        extern const glm::vec3                          WORLD_UP;

        extern const uint32_t                           SHELL_FPS;
        extern const nautilus::NautilusShellContext     SHELL_CONTEXT;
        extern const nautilus::NautilusDimension        SHELL_DIMENSION;
        extern const nautilus::NautilusCameraMode       SHELL_CAMERA_MODE;

    }

}

#endif      // NAUTILUS_DEFAULTS_HPP