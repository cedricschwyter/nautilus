#ifndef NAUTILUS_PIPELINE_CPP
#define NAUTILUS_PIPELINE_CPP

#include "NautilusPipeline.hpp"

NautilusPipeline::NautilusPipeline() {
}

NautilusPipeline::~NautilusPipeline() {
}

nautilus::NautilusStatus NautilusPipeline::compute(const NautilusShaderCompute& _shader) { 
    this->m_compute = _shader; 
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusPipeline::fragment(const NautilusShaderFragment& _shader) {
    this->m_fragment = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusPipeline::geometry(const NautilusShaderGeometry& _shader) {
    this->m_geometry = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusPipeline::tesselation(const NautilusShaderTesselation& _shader) {
    this->m_tesselation = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusPipeline::tesselationControl(const NautilusShaderTesselationControl& _shader) {
    this->m_tesselationControl = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusPipeline::tesselationEvaluation(const NautilusShaderTesselationEvaluation& _shader) {
    this->m_tesselationEvaluation = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusPipeline::vertex(const NautilusShaderVertex& _shader) {
    this->m_vertex = _shader;
    return nautilus::NAUTILUS_STATUS_OK;
}


#endif      // NAUTILUS_PIPELINE_CPP