#ifndef NAUTILUS_SHADER_PIPELINE_HPP
#define NAUTILUS_SHADER_PIPELINE_HPP

#include "NautilusShader.hpp"
#include "NautilusShaderCompute.hpp"
#include "NautilusShaderFragment.hpp"
#include "NautilusShaderGeometry.hpp"
#include "NautilusShaderTesselation.hpp"
#include "NautilusShaderTesselationControl.hpp"
#include "NautilusShaderTesselationEvaluation.hpp"
#include "NautilusShaderVertex.hpp"

class NautilusShaderPipeline {
public:

    /**
     * Default constructor
     */
    NautilusShaderPipeline(void); 

    /**
     * Adds the corresponding shader object to the pipeline
     * @param _shader
     * @return Returns a NautilusStatus status code
     */ 
    NautilusStatus compute(const NautilusShaderCompute& _shader);
    NautilusStatus fragment(const NautilusShaderFragment& _shader);
    NautilusStatus geometry(const NautilusShaderGeometry& _shader);
    NautilusStatus tesselation(const NautilusShaderTesselation& _shader);
    NautilusStatus tesselationControl(const NautilusShaderTesselationControl& _shader);
    NautilusStatus tesselationEvaluation(const NautilusShaderTesselationEvaluation& _shader);
    NautilusStatus vertex(const NautilusShaderVertex& _shader);

    /**
     * Default destructor
     */
    ~NautilusShaderPipeline(void); 

private:

protected:

    NautilusShaderCompute                   m_compute;
    NautilusShaderFragment                  m_fragment;
    NautilusShaderGeometry                  m_geometry;
    NautilusShaderTesselation               m_tesselation;
    NautilusShaderTesselationControl        m_tesselationControl;
    NautilusShaderTesselationEvaluation     m_tesselationEvaluation;
    NautilusShaderVertex                    m_vertex;

};

#endif      // NAUTILUS_SHADER_PIPELINE_HPP