#ifndef NAUTILUS_SHADER_COMPONENT_UNIFORM_CPP
#define NAUTILUS_SHADER_COMPONENT_UNIFORM_CPP

#include "NautilusShaderComponentUniform.hpp"

NautilusShaderComponentUniform::NautilusShaderComponentUniform() {
}

NautilusShaderComponentUniform::NautilusShaderComponentUniform(nautilus::NautilusShaderStage _stage, nautilus::NautilusShaderComponentUniformType _type) {
    this->m_type = nautilus::NAUTILUS_SHADER_COMPONENT_TYPE_UNIFORM;
    this->m_stage = _stage;
    this->m_datatype = _type;
}

NautilusShaderComponentUniform::~NautilusShaderComponentUniform() {
}

#endif      // NAUTILUS_SHADER_COMPONENT_UNIFORM_CPP