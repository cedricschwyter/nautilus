#ifndef NAUTILUS_SHADER_COMPUTE_CPP
#define NAUTILUS_SHADER_COMPUTE_CPP

#include "NautilusShaderCompute.hpp"

NautilusShaderCompute::NautilusShaderCompute() {
    m_glShaderType = GL_COMPUTE_SHADER;
}

NautilusShaderCompute::~NautilusShaderCompute() {
}

#endif      // NAUTILUS_SHADER_COMPUTE_CPP