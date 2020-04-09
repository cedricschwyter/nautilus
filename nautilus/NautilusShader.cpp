#ifndef NAUTILUS_SHADER_CPP
#define NAUTILUS_SHADER_CPP

#include "NautilusShader.hpp"

NautilusShader::NautilusShader() {
}

NautilusShader::NautilusShader(nautilus::NautilusAPI _api) : m_api(_api) {
}

nautilus::NautilusStatus NautilusShader::attach(NautilusShaderComponent* _comp) {
    return nautilus::NAUTILUS_STATUS_OK;
}

NautilusShader::~NautilusShader() {
}

#endif      // NAUTILUS_SHADER_CPP