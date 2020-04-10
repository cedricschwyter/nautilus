#ifndef NAUTILUS_SHADER_COMPONENT_CPP
#define NAUTILUS_SHADER_COMPONENT_CPP

#include "NautilusShaderComponent.hpp"

NautilusShaderComponent::NautilusShaderComponent() {
}

NautilusShaderComponent::~NautilusShaderComponent() {
}

NautilusStatus NautilusShaderComponent::name(const std::string& _name) {
    this->m_name = _name;
    return NAUTILUS_STATUS_OK;
}

NautilusStatus NautilusShaderComponent::value(const std::string& _value) {
    this->m_value = _value;
    return NAUTILUS_STATUS_OK;
}

#endif      // NAUTILUS_SHADER_COMPONENT_CPP