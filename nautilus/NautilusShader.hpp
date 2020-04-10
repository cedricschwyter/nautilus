#ifndef NAUTILUS_SHADER_HPP
#define NAUTILUS_SHADER_HPP

#include "NautilusAPI.hpp"
#include "NautilusStatus.hpp"
#include "NautilusShaderComponent.hpp"
#include "NautilusShaderComponentUniform.hpp"
#include "NautilusShaderComponentUniformType.hpp"
#include "NautilusShaderComponentInOut.hpp"

#include <string>

class NautilusShader {
public:

    /**
     * Default constructor
     */ 
    NautilusShader(void);

    /**
     * Constructor with arguments
     * @param _api The nautilus API to construct shader source for
     */
    NautilusShader(NautilusAPI _api); 

    /**
     * Adds a uniform variable to the shader source
     * @param _comp The shader component to attach to the source
     * @return Returns a nautilus::NautilusStatus status code
     */ 
    NautilusStatus attach(NautilusShaderComponent* _comp);

    /**
     * Default destructor
     */ 
    ~NautilusShader(void);

private:

protected:

    std::string         m_shadersrc;
    NautilusAPI         m_api           = NAUTILUS_API_UNSPECIFIED;

};

#endif      // NAUTILUS_SHADER_HPP