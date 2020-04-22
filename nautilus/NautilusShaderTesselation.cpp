#ifndef NAUTILUS_SHADER_TESSELATION_CPP
#define NAUTILUS_SHADER_TESSELATION_CPP

#include "NautilusShaderTesselation.hpp"

NautilusShaderTesselation::NautilusShaderTesselation() {
}

NautilusShaderTesselation::~NautilusShaderTesselation() {
}

nautilus::NautilusStatus NautilusShaderTesselation::setControl(NautilusShaderTesselationControl* _shader) {
    m_control = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShaderTesselation::setEvaluation(NautilusShaderTesselationEvaluation* _shader) {
    m_evaluation = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

NautilusShaderTesselationControl* NautilusShaderTesselation::control() {
    return m_control;
}

NautilusShaderTesselationEvaluation* NautilusShaderTesselation::evaluation() {
    return m_evaluation;
}

#endif      // NAUTILUS_SHADER_TESSELATION_CPP