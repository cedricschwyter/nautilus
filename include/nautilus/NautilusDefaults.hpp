#ifndef NAUTILUS_DEFAULTS_HPP
#define NAUTILUS_DEFAULTS_HPP

#include <glm/glm.hpp>

namespace nautilus {

    namespace defaults {

        extern const double                         CAMERA_SPEED;
        extern const double                         CAMERA_SENS;
        extern const double                         CAMERA_FOV;

        extern const glm::vec3                      WORLD_ORIGIN;
        extern const glm::vec3                      WORLD_UP_GL;
        extern const glm::vec3                      WORLD_UP_VK;
        extern const glm::vec3                      WORLD_UP;

    }

}

#endif      // NAUTILUS_DEFAULTS_HPP