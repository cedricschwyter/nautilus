#ifndef NAUTILUS_SHADER_TESSELATION_CONTROL_CPP
#define NAUTILUS_SHADER_TESSELATION_CONTROL_CPP

#include "NautilusShaderTesselationControl.hpp"

namespace nautilus {

    NautilusShaderTesselationControl::NautilusShaderTesselationControl() {
        m_glShaderType = GL_TESS_CONTROL_SHADER;
    }

    NautilusShaderTesselationControl::~NautilusShaderTesselationControl() {
    }

}

#endif      // NAUTILUS_SHADER_TESSELATION_CONTROL_CPP