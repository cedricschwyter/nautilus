#ifndef NAUTILUS_SHADER_COMPONENT_IN_OUT_CPP
#define NAUTILUS_SHADER_COMPONENT_IN_OUT_CPP

#include "NautilusShaderComponentInOut.hpp"

NautilusShaderComponentInOut::NautilusShaderComponentInOut() {
}

NautilusShaderComponentInOut::NautilusShaderComponentInOut(nautilus::NautilusShaderStage _orig, nautilus::NautilusShaderStage _dest) {
    m_type = nautilus::NAUTILUS_SHADER_COMPONENT_TYPE_IN_OUT;
    m_orig = _orig;
    m_dest = _dest;
}

NautilusShaderComponentInOut::~NautilusShaderComponentInOut() {
}

#endif      // NAUTILUS_SHADER_COMPONENT_IN_OUT_CPP