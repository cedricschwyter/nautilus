#ifndef NAUTILUS_CAMERA_CPP
#define NAUTILUS_CAMERA_CPP

#include "NautilusCamera.hpp"

NautilusCamera::NautilusCamera() {
}

NautilusCamera::~NautilusCamera() {
}

glm::mat4 NautilusCamera::view() {
    return glm::lookAt(
        this->m_cameraVectors.m_pos, 
        this->m_cameraVectors.m_pos + this->m_cameraVectors.m_frt, 
        this->m_cameraVectors.m_cup);
}

#endif      // NAUTILUS_CAMERA_CPP