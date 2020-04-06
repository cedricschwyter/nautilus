#ifndef NAUTILUS_DEFAULTS_CPP
#define NAUTILUS_DEFAULTS_CPP

#include "NautilusDefaults.hpp"

namespace nautilus {

    namespace defaults {

        const float                         CAMERA_SPEED                            = 2.5f;
        const float                         CAMERA_SENS                             = 0.1f;
        const float                         CAMERA_FOV                              = 105.0f;

        const glm::vec3                     WORLD_ORIGIN                            = glm::vec3(0.0f);
        const glm::vec3                     WORLD_UP_GL                             = glm::vec3(0.0f, 1.0f, 0.0f);
        const glm::vec3                     WORLD_UP_VK                             = glm::vec3(0.0f, -1.0f, 0.0f);
        const glm::vec3                     WORLD_UP                                = glm::vec3(0.0f, 1.0f, 0.0f);

    }

}

#endif      // NAUTILUS_DEFAULTS_CPP