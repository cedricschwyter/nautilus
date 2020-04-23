#ifndef NAUTILUS_CAMERA_CPP
#define NAUTILUS_CAMERA_CPP

#include "NautilusCamera.hpp"

namespace nautilus {

    NautilusCamera::NautilusCamera() {
    }

    NautilusCamera::NautilusCamera(
        NautilusCamera::NautilusCameraVectors       _vec, 
        NautilusCamera::NautilusCameraEulerAngles   _ang,
        float                                       _speed,
        float                                       _sens,
        float                                       _fov) {
        m_cameraVectors       = _vec;
        m_angles              = _ang;
        m_speed               = _speed;
        m_sens                = _sens;
        m_fov                 = _fov;
    }

    NautilusCamera::~NautilusCamera() {
    }

    glm::mat4 NautilusCamera::view() {
        return glm::lookAt(
            m_cameraVectors.m_pos, 
            m_cameraVectors.m_pos + m_cameraVectors.m_frt, 
            m_cameraVectors.m_cup);
    }

    void NautilusCamera::update() {
        glm::vec3 newFront;
        newFront.x = static_cast< float >(glm::cos(glm::radians(m_angles.m_yaw)) * glm::cos(glm::radians(m_angles.m_pitch)));
        newFront.y = static_cast< float >(glm::sin(glm::radians(m_angles.m_pitch)));
        newFront.z = static_cast< float >(glm::sin(glm::radians(m_angles.m_yaw)) * glm::cos(glm::radians(m_angles.m_pitch)));
        m_cameraVectors.m_frt = glm::normalize(newFront);
        m_cameraVectors.m_rgt = glm::normalize(glm::cross(m_cameraVectors.m_frt, m_cameraVectors.m_wup));
        m_cameraVectors.m_cup = glm::normalize(glm::cross(m_cameraVectors.m_rgt, m_cameraVectors.m_frt));
    }

    NautilusStatus NautilusCamera::move(NautilusCameraMovementDirection _dir) {
        static float deltaTime = 0.0f;
        static float lastFrame = 0.0f;
        float currentFrame = static_cast< float >(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        float speed = m_speed * deltaTime;
        switch(_dir) {
            case NAUTILUS_CAMERA_MOVEMENT_DIRECTION_FORWARD:
                m_cameraVectors.m_pos += speed * m_cameraVectors.m_frt;
                break;
            case NAUTILUS_CAMERA_MOVEMENT_DIRECTION_BACKWARD:
                m_cameraVectors.m_pos -= speed * m_cameraVectors.m_frt;
                break;
            case NAUTILUS_CAMERA_MOVEMENT_DIRECTION_LEFT:
                m_cameraVectors.m_pos -= speed * m_cameraVectors.m_rgt;
                break;
            case NAUTILUS_CAMERA_MOVEMENT_DIRECTION_RIGHT:
                m_cameraVectors.m_pos += speed * m_cameraVectors.m_rgt;
                break;
            case NAUTILUS_CAMERA_MOVEMENT_DIRECTION_UP:
                m_cameraVectors.m_pos += speed * m_cameraVectors.m_cup;
                break;
            case NAUTILUS_CAMERA_MOVEMENT_DIRECTION_DOWN:
                m_cameraVectors.m_pos -= speed * m_cameraVectors.m_cup;
                break;
            default:
                logger::log("Unknown movement direction", NAUTILUS_STATUS_FATAL);
                return NAUTILUS_STATUS_FATAL;
        }
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusCamera::move(glm::vec3 _dir) {
        m_cameraVectors.m_pos += m_speed * _dir;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusCamera::moveTo(glm::vec3 _pos) {
        m_cameraVectors.m_pos = _pos;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusCamera::rotate(NautilusCameraCoordinateSystemAxis _rot, float _amt) {
        switch(_rot) {
            case NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_RGT:
                m_angles.m_pitch += m_sens * _amt;
                break;
            case NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_UP:
                m_angles.m_yaw += m_sens * _amt;
                break;
            case NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_FWD:
                m_angles.m_roll += m_sens * _amt;
                break;
            default: 
                logger::log("Invalid view space rotation axis", NAUTILUS_STATUS_FATAL);
                break;
        }
        update();
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusCamera::rotate(glm::vec3 _rot, float _amt) {
        // TODO: implement calculations for arbitrary rotation axis
        update();
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusCamera::rotateTo(NautilusCameraCoordinateSystemAxis _rot, float _amt) {
        switch(_rot) {
            case NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_RGT:
                m_angles.m_pitch+= m_sens * _amt;
                break;
            case NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_UP:
                m_angles.m_yaw = m_sens * _amt;
                break;
            case NAUTILUS_CAMERA_COORDINATE_SYSTEM_AXIS_FWD:
                m_angles.m_roll = m_sens * _amt;
                break;
            default: 
                logger::log("Invalid view space rotation axis", NAUTILUS_STATUS_FATAL);
                break;
        }
        update();
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusCamera::rotateTo(glm::vec3 _rot, float _amt) {
        // TODO: implement calculations for arbitrary rotation axis
        update();
        return NAUTILUS_STATUS_OK;
    }

}

#endif      // NAUTILUS_CAMERA_CPP