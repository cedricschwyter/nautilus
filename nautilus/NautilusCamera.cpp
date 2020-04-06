#ifndef NAUTILUS_CAMERA_CPP
#define NAUTILUS_CAMERA_CPP

#include "NautilusCamera.hpp"

NautilusCamera::NautilusCamera() {
}

NautilusCamera::NautilusCamera(
    NautilusCamera::NautilusCameraVectors       _vec, 
    NautilusCamera::NautilusCameraEulerAngles   _ang,
    double                                      _speed,
    double                                      _sens,
    double                                      _fov) {
    this->m_cameraVectors       = _vec;
    this->m_angles              = _ang;
    this->m_speed               = _speed;
    this->m_sens                = _sens;
    this->m_fov                 = _fov;
}

NautilusCamera::~NautilusCamera() {
}

glm::mat4 NautilusCamera::view() {
    return glm::lookAt(
        this->m_cameraVectors.m_pos, 
        this->m_cameraVectors.m_pos + this->m_cameraVectors.m_frt, 
        this->m_cameraVectors.m_cup);
}

void NautilusCamera::update() {
    glm::vec3 newFront;
    newFront.x = static_cast< float >(glm::cos(glm::radians(this->m_angles.m_yaw)) * glm::cos(glm::radians(this->m_angles.m_pitch)));
    newFront.y = static_cast< float >(glm::sin(glm::radians(this->m_angles.m_pitch)));
    newFront.z = static_cast< float >(glm::sin(glm::radians(this->m_angles.m_yaw)) * glm::cos(glm::radians(this->m_angles.m_pitch)));
    this->m_cameraVectors.m_frt = glm::normalize(newFront);
    this->m_cameraVectors.m_rgt = glm::normalize(glm::cross(this->m_cameraVectors.m_frt, this->m_cameraVectors.m_wup));
    this->m_cameraVectors.m_cup = glm::normalize(glm::cross(this->m_cameraVectors.m_rgt, this->m_cameraVectors.m_frt));
}

nautilus::NautilusStatus NautilusCamera::move(nautilus::NautilusCameraMovementDirection _dir) {
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCamera::move(glm::vec3 _dir) {
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCamera::rotate(nautilus::NautilusCameraCoordinateSystemAxis _rot) {
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCamera::rotate(glm::vec3 _rot) {
    return nautilus::NAUTILUS_STATUS_OK;
}

#endif      // NAUTILUS_CAMERA_CPP