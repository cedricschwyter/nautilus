#ifndef NAUTILUS_SHADER_TESSELATION_CONTROL_HPP
#define NAUTILUS_SHADER_TESSELATION_CONTROL_HPP

#include "NautilusShader.hpp"

class NautilusShaderTesselationControl 
    : public NautilusShader {
public:

    /**
     * Default constructor
     */
    NautilusShaderTesselationControl(void); 

    /**
     * Constructor with argumets
     * Compile shader from source file
     * @param _path The relative path to the source file
     */ 
    NautilusShaderTesselationControl(const std::string& _path);

    /**
     * Default destructor
     */
    ~NautilusShaderTesselationControl(void); 

private:

};

#endif      // NAUTILUS_SHADER_TESSELATION_CONTROL_HPP