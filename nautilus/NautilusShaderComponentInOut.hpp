#ifndef NAUTILUS_SHADER_COMPONENT_IN_OUT_HPP
#define NAUTILUS_SHADER_COMPONENT_IN_OUT_HPP

#include "NautilusShaderComponent.hpp"

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
    NautilusShaderComponentInOut(nautilus::NautilusShaderStage _orig, nautilus::NautilusShaderStage _dest); 

    /**
     * Default destructor
     */
    ~NautilusShaderComponentInOut(void); 

private:

    nautilus::NautilusShaderStage m_orig;
    nautilus::NautilusShaderStage m_dest;

};

#endif      // NAUTILUS_SHADER_COMPONENT_IN_OUT_HPP