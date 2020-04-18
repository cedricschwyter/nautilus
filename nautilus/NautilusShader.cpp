#ifndef NAUTILUS_SHADER_CPP
#define NAUTILUS_SHADER_CPP

#include "NautilusShader.hpp"

NautilusShader::NautilusShader() {
}

NautilusShader::NautilusShader(nautilus::NautilusAPI _api) : m_api(_api) {
}

NautilusShader::NautilusShader(nautilus::NautilusAPI _api, const std::string& _path) : m_api(_api) {
    const std::vector< char > _binary = nautilus::loadFile(_path);
    const char* _shaderCodeBinary = _binary.data();
    switch(_api) {
        case nautilus::NAUTILUS_API_OPENGL:
        break;
        case nautilus::NAUTILUS_API_VULKAN:
        break;
        default:
        break;
    }
}

nautilus::NautilusStatus NautilusShader::attach(NautilusShaderComponent* _comp) {
    return nautilus::NAUTILUS_STATUS_OK;
}

NautilusShader::~NautilusShader() {
}

#endif      // NAUTILUS_SHADER_CPP