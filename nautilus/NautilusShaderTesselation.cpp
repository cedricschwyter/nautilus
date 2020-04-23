#ifndef NAUTILUS_SHADER_TESSELATION_CPP
#define NAUTILUS_SHADER_TESSELATION_CPP

#include "NautilusShaderTesselation.hpp"

namespace nautilus {

    NautilusShaderTesselation::NautilusShaderTesselation() {
    }

    NautilusShaderTesselation::~NautilusShaderTesselation() {
    }

    NautilusStatus NautilusShaderTesselation::setControl(NautilusShaderTesselationControl* _shader) {
        m_control = _shader;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShaderTesselation::setEvaluation(NautilusShaderTesselationEvaluation* _shader) {
        m_evaluation = _shader;
        return NAUTILUS_STATUS_OK;
    }

    NautilusShaderTesselationControl* NautilusShaderTesselation::control() {
        return m_control;
    }

    NautilusShaderTesselationEvaluation* NautilusShaderTesselation::evaluation() {
        return m_evaluation;
    }

}

#endif      // NAUTILUS_SHADER_TESSELATION_CPP