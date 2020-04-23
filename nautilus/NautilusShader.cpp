#ifndef NAUTILUS_SHADER_CPP
#define NAUTILUS_SHADER_CPP

#include "NautilusShader.hpp"
#include "NautilusNS.hpp"

NautilusShader::NautilusShader() {
}

NautilusShader* NautilusShader::fromFile(const std::string& _path) {
    m_path = _path;
    const std::vector< char > _binary = nautilus::loadFile(_path);
    const char* _shaderCodeBinary = _binary.data();
    m_shadersrc = std::string(_shaderCodeBinary);
    return this;
}

nautilus::NautilusStatus NautilusShader::attach(NautilusShaderComponent* _comp) {
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShader::compile(nautilus::NautilusAPI _api) {
    switch(_api) {
    case nautilus::NAUTILUS_API_OPENGL:
        compileOpenGL();
        break;
    case nautilus::NAUTILUS_API_VULKAN:
        compileVulkan();
        break;
    default:
        nautilus::logger::log("Unsupported API", nautilus::NAUTILUS_STATUS_FATAL);
        break;
    }
    return nautilus::NAUTILUS_STATUS_OK;
}

uint32_t NautilusShader::handle() {
    return m_handle;
}

nautilus::NautilusStatus NautilusShader::del(nautilus::NautilusAPI _api) {
    switch(_api) {
    case nautilus::NAUTILUS_API_OPENGL:
        glDeleteShader(m_handle);
        break;
    case nautilus::NAUTILUS_API_VULKAN:
        break;
    default:
        nautilus::logger::log("Unsupported API", nautilus::NAUTILUS_STATUS_FATAL);
        break;
    }
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShader::compileOpenGL() {
    int32_t success;
    char infoLog[512];
    m_handle = glCreateShader(m_glShaderType);
    const char* source = m_shadersrc.c_str();
    glShaderSource(m_handle, 1, &source, nullptr);
    glCompileShader(m_handle);
    glGetShaderiv(m_handle, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(m_handle, 512, nullptr, infoLog);
        if(m_path != "")
            nautilus::logger::log("Failed to compile shader at " + std::string(m_path) + ": " + std::string(infoLog));
        else
            nautilus::logger::log("Failed to compile shader: " + std::string(infoLog)); 
    }
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShader::compileVulkan() {
    return nautilus::NAUTILUS_STATUS_OK;
}

NautilusShader::~NautilusShader() {
}

#endif      // NAUTILUS_SHADER_CPP