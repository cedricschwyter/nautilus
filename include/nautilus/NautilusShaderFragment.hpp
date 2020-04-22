#ifndef NAUTILUS_SHADER_FRAGMENT_HPP
#define NAUTILUS_SHADER_FRAGMENT_HPP

#include "NautilusShader.hpp"

class NautilusShaderFragment 
    : public NautilusShader {
public:

    /**
     * Default constructor
     */
    NautilusShaderFragment(void); 

    /**
     * Constructor with argumets
     * Compile shader from source file
     * @param _path The relative path to the source file
     */ 
    NautilusShaderFragment(const std::string& _path);

    /**
     * Default destructor
     */
    ~NautilusShaderFragment(void); 

private:

};

#endif      // NAUTILUS_SHADER_FRAGMENT_HPP