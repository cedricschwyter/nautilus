#ifndef NAUTILUS_SHADER_TESSELATION_HPP
#define NAUTILUS_SHADER_TESSELATION_HPP

#include "NautilusShaderTesselationControl.hpp"
#include "NautilusShaderTesselationEvaluation.hpp"

class NautilusShaderTesselation {
public:

    /**
     * Default constructor
     */
    NautilusShaderTesselation(void); 

    /**
     * Sets the corresponding shader objects
     * @param _shader The shader object
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus setControl(NautilusShaderTesselationControl* _shader);
    nautilus::NautilusStatus setEvaluation(NautilusShaderTesselationEvaluation* _shader);

    /**
     * Returns the corresponding shader
     * @return Returns a NautilusShader pointer to the corresponding shader
     */ 
    NautilusShaderTesselationControl* control(void);
    NautilusShaderTesselationEvaluation* evaluation(void);

    /**
     * Default destructor
     */
    ~NautilusShaderTesselation(void); 

private:

    NautilusShaderTesselationControl*    m_control;
    NautilusShaderTesselationEvaluation* m_evaluation;

};

#endif      // NAUTILUS_SHADER_TESSELATION_HPP