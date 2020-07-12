#ifndef NAUTILUS_SHADER_COMPONENT_UNIFORM_CPP
#define NAUTILUS_SHADER_COMPONENT_UNIFORM_CPP

#include "NautilusShaderComponentUniform.hpp"

NautilusShaderComponentUniform::NautilusShaderComponentUniform() {
}

NautilusShaderComponentUniform::NautilusShaderComponentUniform(nautilus::NautilusShaderStage _stage, nautilus::NautilusShaderComponentUniformType _type) {
    m_type = nautilus::NAUTILUS_SHADER_COMPONENT_TYPE_UNIFORM;
    m_stage = _stage;
    m_datatype = _type;
}

NautilusShaderComponentUniform::~NautilusShaderComponentUniform() {
}

#endif      // NAUTILUS_SHADER_COMPONENT_UNIFORM_CPP