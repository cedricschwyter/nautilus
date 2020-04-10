#ifndef NAUTILUS_SHADER_PIPELINE_CPP
#define NAUTILUS_SHADER_PIPELINE_CPP

#include "NautilusShaderPipeline.hpp"

NautilusShaderPipeline::NautilusShaderPipeline() {
}

NautilusShaderPipeline::~NautilusShaderPipeline() {
}

NautilusStatus NautilusShaderPipeline::compute(const NautilusShaderCompute& _shader) { 
    this->m_compute = _shader; 
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShaderPipeline::fragment(const NautilusShaderFragment& _shader) {
    this->m_fragment = _shader;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShaderPipeline::geometry(const NautilusShaderGeometry& _shader) {
    this->m_geometry = _shader;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShaderPipeline::tesselation(const NautilusShaderTesselation& _shader) {
    this->m_tesselation = _shader;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShaderPipeline::tesselationControl(const NautilusShaderTesselationControl& _shader) {
    this->m_tesselationControl = _shader;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShaderPipeline::tesselationEvaluation(const NautilusShaderTesselationEvaluation& _shader) {
    this->m_tesselationEvaluation = _shader;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShaderPipeline::vertex(const NautilusShaderVertex& _shader) {
    this->m_vertex = _shader;
    return NAUTILUS_STATUS_OK;
}


#endif      // NAUTILUS_SHADER_PIPELINE_CPP