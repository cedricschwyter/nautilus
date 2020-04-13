#ifndef NAUTILUS_SHADER_PIPELINE_CPP
#define NAUTILUS_SHADER_PIPELINE_CPP

#include "NautilusShaderPipeline.hpp"

NautilusShaderPipeline::NautilusShaderPipeline() {
}

NautilusShaderPipeline::~NautilusShaderPipeline() {
}

nautilus::NautilusStatus NautilusShaderPipeline::compute(const NautilusShaderCompute& _shader) { 
    this->m_compute = _shader; 
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShaderPipeline::fragment(const NautilusShaderFragment& _shader) {
    this->m_fragment = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShaderPipeline::geometry(const NautilusShaderGeometry& _shader) {
    this->m_geometry = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShaderPipeline::tesselation(const NautilusShaderTesselation& _shader) {
    this->m_tesselation = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShaderPipeline::tesselationControl(const NautilusShaderTesselationControl& _shader) {
    this->m_tesselationControl = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShaderPipeline::tesselationEvaluation(const NautilusShaderTesselationEvaluation& _shader) {
    this->m_tesselationEvaluation = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShaderPipeline::vertex(const NautilusShaderVertex& _shader) {
    this->m_vertex = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}


#endif      // NAUTILUS_SHADER_PIPELINE_CPP