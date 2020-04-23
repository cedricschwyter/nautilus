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

namespace nautilus {

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
        NautilusStatus compute(NautilusShaderCompute* _shader);
        NautilusStatus fragment(NautilusShaderFragment* _shader);
        NautilusStatus geometry(NautilusShaderGeometry* _shader);
        NautilusStatus tesselation(NautilusShaderTesselation* _shader);
        NautilusStatus tesselationControl(NautilusShaderTesselationControl* _shader);
        NautilusStatus tesselationEvaluation(NautilusShaderTesselationEvaluation* _shader);
        NautilusStatus vertex(NautilusShaderVertex* _shader);

        /**
         * Adds the corresponding shader object to the pipeline
         * @param _path The path to the shader source on disk
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus compute(const std::string& _path);
        NautilusStatus fragment(const std::string& _path);
        NautilusStatus geometry(const std::string& _path);
        NautilusStatus tesselationControl(const std::string& _path);
        NautilusStatus tesselationEvaluation(const std::string& _path);
        NautilusStatus vertex(const std::string& _path);

        /**
         * Handles pipeline attachment
         * @param _api The NautilusAPI to compile shader pipeline for
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus attach(NautilusAPI _api);

        /**
         * Returns the pipelines identifier
         * @return Returns a string as an identifier
         */ 
        const std::string& identifier(void);

        /**
         * Binds and uses a pipeline
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus activate(NautilusAPI _api);

        /**
         * Default destructor
         */
        ~NautilusPipeline(void); 

    private:

    protected:

        std::map< NautilusShaderStage, NautilusShader* >      m_shaders;
        uint32_t                                                        m_program       = 0;
        std::string                                                     m_identifier;

        /**
         * Compiles and links a shader pipeline
         * @param _api The NautilusAPI to compile shader pipeline for
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus compile(NautilusAPI _api);

        /**
         * Compiles and links a shader pipeline for OpenGL
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus compileOpenGL(void);

        /**
         * Compiles and links a shader pipeline for Vulkan
         * @return Returns a NautilusStatus status code
         */ 
        NautilusStatus compileVulkan(void);

    };

}

#endif      // NAUTILUS_PIPELINE_HPP