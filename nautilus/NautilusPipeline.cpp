#ifndef NAUTILUS_PIPELINE_CPP
#define NAUTILUS_PIPELINE_CPP

#include "NautilusPipeline.hpp"

namespace nautilus {

    NautilusPipeline::NautilusPipeline() {
    }

    NautilusPipeline::NautilusPipeline(const std::string& _identifier) : m_identifier(_identifier) {
    }

    NautilusPipeline::~NautilusPipeline() {
        for(auto entry : m_shaders)
            delete entry.second;
    }

    NautilusStatus NautilusPipeline::compute(NautilusShaderCompute* _shader) { 
        m_shaders[NAUTILUS_SHADER_STAGE_COMPUTE] = _shader; 
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::fragment(NautilusShaderFragment* _shader) {
        m_shaders[NAUTILUS_SHADER_STAGE_FRAGMENT] = _shader; 
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::geometry(NautilusShaderGeometry* _shader) {
        m_shaders[NAUTILUS_SHADER_STAGE_GEOMETRY] = _shader; 
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::tesselation(NautilusShaderTesselation* _shader) {
        m_shaders[NAUTILUS_SHADER_STAGE_TESSELATION_CONTROL] = _shader->control(); 
        m_shaders[NAUTILUS_SHADER_STAGE_TESSELATION_EVALUATION] = _shader->evaluation(); 
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::tesselationControl(NautilusShaderTesselationControl* _shader) {
        m_shaders[NAUTILUS_SHADER_STAGE_TESSELATION_CONTROL] = _shader; 
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::tesselationEvaluation(NautilusShaderTesselationEvaluation* _shader) {
        m_shaders[NAUTILUS_SHADER_STAGE_TESSELATION_EVALUATION] = _shader; 
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::vertex(NautilusShaderVertex* _shader) {
        m_shaders[NAUTILUS_SHADER_STAGE_VERTEX] = _shader; 
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::compute(const std::string& _path) { 
        m_shaders[NAUTILUS_SHADER_STAGE_COMPUTE] = (new NautilusShaderCompute())->fromFile(_path); 
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::fragment(const std::string& _path) {
        m_shaders[NAUTILUS_SHADER_STAGE_FRAGMENT] = (new NautilusShaderFragment())->fromFile(_path); 
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::geometry(const std::string& _path) {
        m_shaders[NAUTILUS_SHADER_STAGE_GEOMETRY] = (new NautilusShaderGeometry())->fromFile(_path); 
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::tesselationControl(const std::string& _path) {
        m_shaders[NAUTILUS_SHADER_STAGE_TESSELATION_CONTROL] = (new NautilusShaderTesselationControl())->fromFile(_path); 
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::tesselationEvaluation(const std::string& _path) {
        m_shaders[NAUTILUS_SHADER_STAGE_TESSELATION_EVALUATION] = (new NautilusShaderTesselationEvaluation())->fromFile(_path); 
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::vertex(const std::string& _path) {
        m_shaders[NAUTILUS_SHADER_STAGE_VERTEX] = (new NautilusShaderVertex())->fromFile(_path); 
        return NAUTILUS_STATUS_OK;
    }


    NautilusStatus NautilusPipeline::attach(NautilusAPI _api) {
        compile(_api);
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::compile(NautilusAPI _api) {
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

    const std::string& NautilusPipeline::identifier() {
        return m_identifier;
    }

    NautilusStatus NautilusPipeline::activate(NautilusAPI _api) {
        switch(_api) {
        case NAUTILUS_API_OPENGL:
            glUseProgram(m_program);
            break;
        case NAUTILUS_API_VULKAN:
            break;
        default:
            logger::log("Unsupported API", NAUTILUS_STATUS_FATAL);
            break;
        }
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::compileOpenGL() {
        for(auto entry : m_shaders) 
            entry.second->compile(NAUTILUS_API_OPENGL);
        m_program = glCreateProgram();
        for(auto entry : m_shaders)
            glAttachShader(m_program, entry.second->handle());
        glLinkProgram(m_program);
        int32_t success;
        char infoLog[512];
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
            logger::log("Failed to link shader: " + std::string(infoLog), NAUTILUS_STATUS_FATAL);
        }
        for(auto entry : m_shaders)
            entry.second->del(NAUTILUS_API_OPENGL);
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusPipeline::compileVulkan() {
        return NAUTILUS_STATUS_OK;
    }

}

#endif      // NAUTILUS_PIPELINE_CPP
