#ifndef NAUTILUS_DEFAULTS_CPP
#define NAUTILUS_DEFAULTS_CPP

#include "NautilusDefaults.hpp"

namespace nautilus {

    namespace defaults {

        const std::string                       CONTEXT_NAME            = "Nautilus by D3PSI";
        const std::string                       CONTEXT_NAME_OPENGL     = "OpenGL Example with Nautilus by D3PSI";
        const std::string                       CONTEXT_NAME_VULKAN     = "Vulkan Example with Nautilus by D3PSI";

        const std::string                       LOG_DIR                 = "logs/";
        const std::string                       RESOURCE_DIR            = "res/";
        const std::string                       IMAGE_DIR               = "res/images/";
        const std::string                       ICON_DIR                = "res/images/icons";
        const std::string                       SHADER_DIR              = "res/shaders";
        const std::string                       SHADER_DIR_OPENGL       = "res/shaders/opengl/";
        const std::string                       SHADER_DIR_VULKAN       = "res/shaders/vulkan/";
        const std::string                       SHADER_DIR_OPENGL_V330  = "res/shaders/opengl/v330/";

        const float                             CAMERA_SPEED            = 2.5f;
        const float                             CAMERA_SENS             = 0.1f;
        const float                             CAMERA_FOV              = 105.0f;
        const float                             CAMERA_MIN_FOV          = 1.0f;
        const float                             CAMERA_MAX_FOV          = 130.0f;
        const float                             CAMERA_MIN_PITCH        = -89.0f;
        const float                             CAMERA_MAX_PITCH        = 89.0f;

        const glm::vec3                         WORLD_ORIGIN            = glm::vec3(0.0f);
        const glm::vec3                         WORLD_UP_OPENGL         = glm::vec3(0.0f, 1.0f, 0.0f);
        const glm::vec3                         WORLD_UP_VULKAN         = glm::vec3(0.0f, -1.0f, 0.0f);
        const glm::vec3                         WORLD_UP                = glm::vec3(0.0f, 1.0f, 0.0f);

        const uint32_t                          SHELL_FPS               = 60;
        const NautilusShellContext    SHELL_CONTEXT           = NAUTILUS_SHELL_CONTEXT_WINDOWED;
        const NautilusDimension       SHELL_DIMENSION         = NAUTILUS_DIMENSION_2D;
        const NautilusCameraMode      SHELL_CAMERA_MODE       = NAUTILUS_CAMERA_MODE_2D;

    }

}

#endif      // NAUTILUS_DEFAULTS_CPP