#ifndef NAUTILUS_SHADER_VERTEX_HPP
#define NAUTILUS_SHADER_VERTEX_HPP

#include "NautilusShader.hpp"

class NautilusShaderVertex
    : public NautilusShader {
public:

    /**
     * Default constructor
     */
    NautilusShaderVertex(void); 

    /**
     * Constructor with argumets
     * Compile shader from source file
     * @param _path The relative path to the source file
     */ 
    NautilusShaderVertex(const std::string& _path);

    /**
     * Default destructor
     */
    ~NautilusShaderVertex(void); 

private:

};

#endif      // NAUTILUS_SHADER_VERTEX_HPP