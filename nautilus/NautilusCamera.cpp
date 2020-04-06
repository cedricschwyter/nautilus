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
    switch(_dir) {
        case nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_FORWARD:
            this->m_cameraVectors.m_pos += this->m_speed * this->m_cameraVectors.m_frt;
            break;
        case nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_BACKWARD:
            this->m_cameraVectors.m_pos -= this->m_speed * this->m_cameraVectors.m_frt;
            break;
        case nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_LEFT:
            this->m_cameraVectors.m_pos -= this->m_speed * this->m_cameraVectors.m_rgt;
            break;
        case nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_RIGHT:
            this->m_cameraVectors.m_pos += this->m_speed * this->m_cameraVectors.m_rgt;
            break;
        case nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_UP:
            this->m_cameraVectors.m_pos += this->m_speed * this->m_cameraVectors.m_cup;
            break;
        case nautilus::NAUTILUS_CAMERA_MOVEMENT_DIRECTION_DOWN:
            this->m_cameraVectors.m_pos -= this->m_speed * this->m_cameraVectors.m_cup;
            break;
        default:
            nautilus::logger::log("Unknown movement direction", nautilus::NAUTILUS_STATUS_FATAL);
            return nautilus::NAUTILUS_STATUS_FATAL;
    }
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCamera::move(glm::vec3 _dir) {
    this->m_cameraVectors.m_pos += this->m_speed * _dir;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCamera::moveTo(glm::vec3 _pos) {
    this->m_cameraVectors.m_pos = _pos;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCamera::rotate(nautilus::NautilusCameraCoordinateSystemAxis _rot, float _amt) {
    switch(_rot) {
        case nautilus::NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_X:
            this->m_angles.m_pitch += this->m_sens * _amt;
            break;
        case nautilus::NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_Y:
            this->m_angles.m_yaw += this->m_sens * _amt;
            break;
        case nautilus::NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_Z:
            this->m_angles.m_roll += this->m_sens * _amt;
            break;
        default: 
            nautilus::logger::log("Invalid view space rotation axis", nautilus::NAUTILUS_STATUS_FATAL);
            break;
    }
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCamera::rotate(glm::vec3 _rot, float _amt) {
    // TODO: implement calculations for arbitrary rotation axis
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCamera::rotateTo(nautilus::NautilusCameraCoordinateSystemAxis _rot, float _amt) {
    switch(_rot) {
        case nautilus::NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_X:
            this->m_angles.m_pitch+= this->m_sens * _amt;
            break;
        case nautilus::NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_Y:
            this->m_angles.m_yaw = this->m_sens * _amt;
            break;
        case nautilus::NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_Z:
            this->m_angles.m_roll = this->m_sens * _amt;
            break;
        default: 
            nautilus::logger::log("Invalid view space rotation axis", nautilus::NAUTILUS_STATUS_FATAL);
            break;
    }
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusCamera::rotateTo(glm::vec3 _rot, float _amt) {
    // TODO: implement calculations for arbitrary rotation axis
    return nautilus::NAUTILUS_STATUS_OK;
}

#endif      // NAUTILUS_CAMERA_CPP