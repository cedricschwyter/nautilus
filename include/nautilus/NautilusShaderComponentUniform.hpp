#ifndef NAUTILUS_SHADER_COMPONENT_UNIFORM_HPP
#define NAUTILUS_SHADER_COMPONENT_UNIFORM_HPP

#include "NautilusShaderComponent.hpp"
#include "NautilusShaderComponentType.hpp"
#include "NautilusShaderComponentUniformType.hpp"

namespace nautilus {

    class NautilusShaderComponentUniform
        : public NautilusShaderComponent {
    public:

        /**
         * Default constructor
         */
        NautilusShaderComponentUniform(void); 

        /**
         * Constructor witha arguments
         * @param _stage The uniform's shader stage
         * @param _type The uniform's type
         */
        NautilusShaderComponentUniform(NautilusShaderStage _stage, NautilusShaderComponentUniformType _type); 

        /**
         * Default destructor
         */ 
        ~NautilusShaderComponentUniform(void);

    private:

        NautilusShaderStage                   m_stage;
        NautilusShaderComponentUniformType    m_datatype;

    protected:

    };

}

#endif      // NAUTILUS_SHADER_COMPONENT_UNIFORM_HPP