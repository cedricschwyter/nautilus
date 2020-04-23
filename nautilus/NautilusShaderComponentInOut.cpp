#ifndef NAUTILUS_SHADER_COMPONENT_IN_OUT_CPP
#define NAUTILUS_SHADER_COMPONENT_IN_OUT_CPP

#include "NautilusShaderComponentInOut.hpp"

namespace nautilus {

    NautilusShaderComponentInOut::NautilusShaderComponentInOut() {
    }

    NautilusShaderComponentInOut::NautilusShaderComponentInOut(NautilusShaderStage _orig, NautilusShaderStage _dest) {
        m_type = NAUTILUS_SHADER_COMPONENT_TYPE_IN_OUT;
        m_orig = _orig;
        m_dest = _dest;
    }

    NautilusShaderComponentInOut::~NautilusShaderComponentInOut() {
    }

}

#endif      // NAUTILUS_SHADER_COMPONENT_IN_OUT_CPP