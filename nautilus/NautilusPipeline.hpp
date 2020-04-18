#ifndef NAUTILUS_PIPELINE_HPP
#define NAUTILUS_PIPELINE_HPP

#include "NautilusShader.hpp"
#include "NautilusShaderCompute.hpp"
#include "NautilusShaderFragment.hpp"
#include "NautilusShaderGeometry.hpp"
#include "NautilusShaderTesselation.hpp"
#include "NautilusShaderTesselationControl.hpp"
#include "NautilusShaderTesselationEvaluation.hpp"
#include "NautilusShaderVertex.hpp"

class NautilusPipeline {
public:

    /**
     * Default constructor
     */
    NautilusPipeline(void); 

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
     * Handles pipeline attachment
     * @return Returns a nautilus::NautilusStatus status code
     */ 
    nautilus::NautilusStatus attach(void);

    /**
     * Default destructor
     */
    ~NautilusPipeline(void); 

private:

protected:

    nautilus::NautilusAPI                   m_api                   = nautilus::NAUTILUS_API_UNSPECIFIED;

    NautilusShaderCompute                   m_compute;
    NautilusShaderFragment                  m_fragment;
    NautilusShaderGeometry                  m_geometry;
    NautilusShaderTesselation               m_tesselation;
    NautilusShaderTesselationControl        m_tesselationControl;
    NautilusShaderTesselationEvaluation     m_tesselationEvaluation;
    NautilusShaderVertex                    m_vertex;

    /**
     * Compiles and links a shader program
     * @return Returns a nautilus::NautilusStatus status code
     */ 
    nautilus::NautilusStatus compile(void);

};

#endif      // NAUTILUS_PIPELINE_HPP