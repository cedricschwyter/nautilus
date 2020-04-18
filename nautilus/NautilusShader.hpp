#ifndef NAUTILUS_SHADER_HPP
#define NAUTILUS_SHADER_HPP

#include "NautilusAPI.hpp"
#include "NautilusStatus.hpp"
#include "NautilusShaderComponent.hpp"
#include "NautilusShaderComponentUniform.hpp"
#include "NautilusShaderComponentUniformType.hpp"
#include "NautilusShaderComponentInOut.hpp"

#include <string>
#include <vector>

class NautilusShader {
public:

    /**
     * Default constructor
     */ 
    NautilusShader(void);

    /**
     * Constructor with arguments
     * @param _api The nautilus api to construct shader source for
     */
    NautilusShader(nautilus::NautilusAPI _api); 

    /**
     * Constructor with argumets
     * Compile shader from source file
     * @param _api The nautilus api to construct shader for
     * @param _path The relative path to the source file
     */ 
    NautilusShader(nautilus::NautilusAPI _api, const std::string& _path);

    /**
     * Adds a uniform variable to the shader source
     * @param _comp The shader component to attach to the source
     * @return Returns a nautilus::NautilusStatus status code
     */ 
    nautilus::NautilusStatus attach(NautilusShaderComponent* _comp);

    /**
     * Default destructor
     */ 
    ~NautilusShader(void);

private:

protected:

    std::string                     m_shadersrc;
    nautilus::NautilusAPI           m_api           = nautilus::NAUTILUS_API_UNSPECIFIED;

};

#endif      // NAUTILUS_SHADER_HPP