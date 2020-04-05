#ifndef NAUTILUS_DEFAULTS_CPP
#define NAUTILUS_DEFAULTS_CPP

#include "NautilusDefaults.hpp"

namespace nautilus {

    namespace defaults {

        const double                        CAMERA_SPEED                            = 2.5;
        const double                        CAMERA_SENS                             = 0.1;
        const double                        CAMERA_FOV                              = 105.0;

        const glm::vec3                     WORLD_ORIGIN                            = glm::vec3(0.0f);
        const glm::vec3                     WORLD_UP_GL                             = glm::vec3(0.0f, 1.0f, 0.0f);
        const glm::vec3                     WORLD_UP_VK                             = glm::vec3(0.0f, -1.0f, 0.0f);
        const glm::vec3                     WORLD_UP                                = glm::vec3(0.0f, 1.0f, 0.0f);

    }

}

#endif      // NAUTILUS_DEFAULTS_CPP