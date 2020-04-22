#ifndef NAUTILUS_SHADER_TESSELATION_EVALUATION_HPP
#define NAUTILUS_SHADER_TESSELATION_EVALUATION_HPP

#include "NautilusShader.hpp"

class NautilusShaderTesselationEvaluation
    : public NautilusShader {
public:

    /**
     * Default constructor
     */
    NautilusShaderTesselationEvaluation(void); 

    /**
     * Constructor with argumets
     * Compile shader from source file
     * @param _path The relative path to the source file
     */ 
    NautilusShaderTesselationEvaluation(const std::string& _path);

    /**
     * Default destructor
     */
    ~NautilusShaderTesselationEvaluation(void); 

private:

};

#endif      // NAUTILUS_SHADER_TESSELATION_EVALUATION_HPP