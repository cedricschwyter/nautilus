#ifndef NAUTILUS_SHADER_TESSELATION_CPP
#define NAUTILUS_SHADER_TESSELATION_CPP

#include "NautilusShaderTesselation.hpp"

NautilusShaderTesselation::NautilusShaderTesselation() {
}

NautilusShaderTesselation::~NautilusShaderTesselation() {
}

nautilus::NautilusStatus NautilusShaderTesselation::setControl(const NautilusShaderTesselationControl& _shader) {
    this->m_control = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShaderTesselation::setEvaluation(const NautilusShaderTesselationEvaluation& _shader) {
    this->m_evaluation = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

NautilusShaderTesselationControl NautilusShaderTesselation::control() {
    return this->m_control;
}

NautilusShaderTesselationEvaluation NautilusShaderTesselation::evaluation() {
    return this->m_evaluation;
}

#endif      // NAUTILUS_SHADER_TESSELATION_CPP