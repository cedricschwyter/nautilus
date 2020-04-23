#ifndef NAUTILUS_SHADER_COMPONENT_IN_OUT_HPP
#define NAUTILUS_SHADER_COMPONENT_IN_OUT_HPP

#include "NautilusShaderComponent.hpp"

namespace nautilus {

    class NautilusShaderComponentInOut
        : public NautilusShaderComponent {
    public:

        /**
         * Default constructor
         */
        NautilusShaderComponentInOut(void); 

        /**
         * Constructor with arguments
         * @param _orig The shader stage where the passed-on variable originates
         * @param _dest The destination shader stage
         */
        NautilusShaderComponentInOut(NautilusShaderStage _orig, NautilusShaderStage _dest); 

        /**
         * Default destructor
         */
        ~NautilusShaderComponentInOut(void); 

    private:

        NautilusShaderStage m_orig;
        NautilusShaderStage m_dest;

    };

}

#endif      // NAUTILUS_SHADER_COMPONENT_IN_OUT_HPP