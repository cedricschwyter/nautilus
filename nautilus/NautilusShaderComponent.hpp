#ifndef NAUTILUS_SHADER_COMPONENT_HPP
#define NAUTILUS_SHADER_COMPONENT_HPP

#include "NautilusShaderComponentType.hpp"
#include "NautilusStatus.hpp"

#include <string>

class NautilusShaderComponent {
public:

    /**
     * Default constructor
     */
    NautilusShaderComponent(void); 

    /**
     * Gives the shader component a name
     * @param _name The name of the component
     * @return Returns a NautilusStatus status code 
     */ 
    virtual NautilusStatus name(const std::string& _name);

    /**
     * Sets the value of the shader component
     * @param _value The value of the component
     * @return Returns a NautilusStatus status code
     */  
    virtual NautilusStatus value(const std::string& _value);

    /**
     * Default destructor
     */
    ~NautilusShaderComponent(void);

private:

protected:

    std::string                             m_name;
    std::string                             m_value;
    nautilus::NautilusShaderComponentType   m_type = nautilus::NAUTILUS_SHADER_COMPONENT_TYPE_UNSPECIFIED;

};

#endif         // NAUTILUS_SHADER_COMPONENT_HPP