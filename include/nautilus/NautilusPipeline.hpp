#ifndef NAUTILUS_PIPELINE_HPP
#define NAUTILUS_PIPELINE_HPP

#include "NautilusLogger.hpp"
#include "NautilusShader.hpp"
#include "NautilusShaderCompute.hpp"
#include "NautilusShaderFragment.hpp"
#include "NautilusShaderGeometry.hpp"
#include "NautilusShaderTesselation.hpp"
#include "NautilusShaderTesselationControl.hpp"
#include "NautilusShaderTesselationEvaluation.hpp"
#include "NautilusShaderVertex.hpp"

#include <map>

class NautilusPipeline {
public:

    /**
     * Default constructor
     */
    NautilusPipeline(void); 

    /**
     * Constructor with arguments
     * @param _identifier A unique string identifier for the pipeline
     */
    NautilusPipeline(const std::string& _identifier); 

    /**
     * Adds the corresponding shader object to the pipeline
     * @param _shader The shader to add to the pipeline
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus compute(NautilusShaderCompute& _shader);
    nautilus::NautilusStatus fragment(NautilusShaderFragment& _shader);
    nautilus::NautilusStatus geometry(NautilusShaderGeometry& _shader);
    nautilus::NautilusStatus tesselation(NautilusShaderTesselation& _shader);
    nautilus::NautilusStatus tesselationControl(NautilusShaderTesselationControl& _shader);
    nautilus::NautilusStatus tesselationEvaluation(NautilusShaderTesselationEvaluation& _shader);
    nautilus::NautilusStatus vertex(NautilusShaderVertex& _shader);

    /**
     * Handles pipeline attachment
     * @param _api The NautilusAPI to compile shader pipeline for
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus attach(nautilus::NautilusAPI _api);

    /**
     * Returns the pipelines identifier
     * @return Returns a string as an identifier
     */ 
    const std::string& identifier(void);

    /**
     * Binds and uses a pipeline
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus activate(nautilus::NautilusAPI _api);

    /**
     * Default destructor
     */
    ~NautilusPipeline(void); 

private:

protected:

    std::map< nautilus::NautilusShaderStage, NautilusShader* >      m_shaders;
    uint32_t                                                        m_program       = 0;
    std::string                                                     m_identifier;

    /**
     * Compiles and links a shader pipeline
     * @param _api The NautilusAPI to compile shader pipeline for
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus compile(nautilus::NautilusAPI _api);

    /**
     * Compiles and links a shader pipeline for OpenGL
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus compileOpenGL(void);

    /**
     * Compiles and links a shader pipeline for Vulkan
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus compileVulkan(void);

};

#endif      // NAUTILUS_PIPELINE_HPP