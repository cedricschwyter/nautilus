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
    nautilus::NautilusStatus compute(const NautilusShaderCompute& _shader);
    nautilus::NautilusStatus fragment(const NautilusShaderFragment& _shader);
    nautilus::NautilusStatus geometry(const NautilusShaderGeometry& _shader);
    nautilus::NautilusStatus tesselation(const NautilusShaderTesselation& _shader);
    nautilus::NautilusStatus tesselationControl(const NautilusShaderTesselationControl& _shader);
    nautilus::NautilusStatus tesselationEvaluation(const NautilusShaderTesselationEvaluation& _shader);
    nautilus::NautilusStatus vertex(const NautilusShaderVertex& _shader);

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