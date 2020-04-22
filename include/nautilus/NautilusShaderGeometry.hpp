#ifndef NAUTILUS_SHADER_GEOMETRY_HPP
#define NAUTILUS_SHADER_GEOMETRY_HPP

#include "NautilusShader.hpp"

class NautilusShaderGeometry
    : public NautilusShader {
public:

    /**
     * Default constructor
     */
    NautilusShaderGeometry(void); 

    /**
     * Constructor with argumets
     * Compile shader from source file
     * @param _path The relative path to the source file
     */ 
    NautilusShaderGeometry(const std::string& _path);

    /**
     * Default destructor
     */
    ~NautilusShaderGeometry(void); 

private:

};

#endif      // NAUTILUS_SHADER_GEOMETRY_HPP