#ifndef NAUTILUS_DEFAULTS_HPP
#define NAUTILUS_DEFAULTS_HPP

#include <glm/glm.hpp>

namespace nautilus {

    namespace defaults {

        extern const float                          CAMERA_SPEED;
        extern const float                          CAMERA_SENS;
        extern const float                          CAMERA_FOV;
        extern const float                          CAMERA_MIN_FOV;
        extern const float                          CAMERA_MAX_FOV;
        extern const float                          CAMERA_MIN_PITCH;
        extern const float                          CAMERA_MAX_PITCH;

        extern const glm::vec3                      WORLD_ORIGIN;
        extern const glm::vec3                      WORLD_UP_GL;
        extern const glm::vec3                      WORLD_UP_VK;
        extern const glm::vec3                      WORLD_UP;

    }

}

#endif      // NAUTILUS_DEFAULTS_HPP