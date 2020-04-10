#ifndef NAUTILUS_SHADER_TESSELATION_CPP
#define NAUTILUS_SHADER_TESSELATION_CPP

#include "NautilusShaderTesselation.hpp"

NautilusShaderTesselation::NautilusShaderTesselation() {
}

NautilusShaderTesselation::~NautilusShaderTesselation() {
}

NautilusStatus NautilusShaderTesselation::setControl(const NautilusShaderTesselationControl& _shader) {
    this->m_control = _shader;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShaderTesselation::setEvaluation(const NautilusShaderTesselationEvaluation& _shader) {
    this->m_evaluation = _shader;
    return NAUTILUS_STATUS_OK;
}

NautilusShaderTesselationControl NautilusShaderTesselation::control() {
    return this->m_control;
}

NautilusShaderTesselationEvaluation NautilusShaderTesselation::evaluation() {
    return this->m_evaluation;
}

#endif      // NAUTILUS_SHADER_TESSELATION_CPP