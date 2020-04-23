#ifndef NAUTILUS_SHADER_COMPONENT_UNIFORM_CPP
#define NAUTILUS_SHADER_COMPONENT_UNIFORM_CPP

#include "NautilusShaderComponentUniform.hpp"

namespace nautilus {

    NautilusShaderComponentUniform::NautilusShaderComponentUniform() {
    }

    NautilusShaderComponentUniform::NautilusShaderComponentUniform(NautilusShaderStage _stage, NautilusShaderComponentUniformType _type) {
        m_type = NAUTILUS_SHADER_COMPONENT_TYPE_UNIFORM;
        m_stage = _stage;
        m_datatype = _type;
    }

    NautilusShaderComponentUniform::~NautilusShaderComponentUniform() {
    }

}

#endif      // NAUTILUS_SHADER_COMPONENT_UNIFORM_CPP