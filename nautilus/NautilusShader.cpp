#ifndef NAUTILUS_SHADER_CPP
#define NAUTILUS_SHADER_CPP

#include "NautilusShader.hpp"
#include "NautilusUtil.hpp"

namespace nautilus {

    NautilusShader::NautilusShader() {
    }

    NautilusShader* NautilusShader::fromFile(const std::string& _path) {
        m_path = _path;
        const std::vector< char > _binary = util::loadFile(_path);
        const char* _shaderCodeBinary = _binary.data();
        m_shadersrc = std::string(_shaderCodeBinary);
        return this;
    }

    NautilusStatus NautilusShader::attach(NautilusShaderComponent* _comp) {
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShader::compile(NautilusAPI _api) {
        switch(_api) {
        case NAUTILUS_API_OPENGL:
            compileOpenGL();
            break;
        case NAUTILUS_API_VULKAN:
            compileVulkan();
            break;
        default:
            logger::log("Unsupported API", NAUTILUS_STATUS_FATAL);
            break;
        }
        return NAUTILUS_STATUS_OK;
    }

    uint32_t NautilusShader::handle() {
        return m_handle;
    }

    NautilusStatus NautilusShader::del(NautilusAPI _api) {
        switch(_api) {
        case NAUTILUS_API_OPENGL:
            glDeleteShader(m_handle);
            break;
        case NAUTILUS_API_VULKAN:
            break;
        default:
            logger::log("Unsupported API", NAUTILUS_STATUS_FATAL);
            break;
        }
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShader::compileOpenGL() {
        int32_t success;
        char infoLog[512];
        m_handle = glCreateShader(m_glShaderType);
        if(m_handle == 0) logger::log("Failed to get shader handle", NAUTILUS_STATUS_FATAL);
        const char* source = m_shadersrc.c_str();
        glShaderSource(m_handle, 1, &source, nullptr);
        glCompileShader(m_handle);
        std::cout << m_handle << std::endl;
        glGetShaderiv(m_handle, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(m_handle, 512, nullptr, infoLog);
            if(m_path != "")
                logger::log("Failed to compile shader at " + std::string(m_path) + ": " + std::string(infoLog), NAUTILUS_STATUS_FATAL);
            else
                logger::log("Failed to compile shader: " + std::string(infoLog), NAUTILUS_STATUS_FATAL); 
        }
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShader::compileVulkan() {
        return NAUTILUS_STATUS_OK;
    }

    NautilusShader::~NautilusShader() {
    }

}

#endif      // NAUTILUS_SHADER_CPP