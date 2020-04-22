#ifndef NAUTILUS_SHADER_COMPUTE_HPP
#define NAUTILUS_SHADER_COMPUTE_HPP

#include "NautilusShader.hpp"

class NautilusShaderCompute 
    : public NautilusShader {
public:

    /**
     * Default constructor
     */
    NautilusShaderCompute(void); 

    /**
     * Constructor with argumets
     * Compile shader from source file
     * @param _path The relative path to the source file
     */ 
    NautilusShaderCompute(const std::string& _path);

    /**
     * Default destructor
     */
    ~NautilusShaderCompute(void); 

private:

};

#endif      // NAUTILUS_SHADER_COMPUTE_HPP