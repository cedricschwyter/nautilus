#ifndef NAUTILUS_SHADER_COMPONENT_CPP
#define NAUTILUS_SHADER_COMPONENT_CPP

#include "NautilusShaderComponent.hpp"

NautilusShaderComponent::NautilusShaderComponent() {
}

NautilusShaderComponent::~NautilusShaderComponent() {
}

nautilus::NautilusStatus NautilusShaderComponent::name(const std::string& _name) {
    this->m_name = _name;
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusShaderComponent::value(const std::string& _value) {
    this->m_value = _value;
    return nautilus::NAUTILUS_STATUS_OK;
}

#endif      // NAUTILUS_SHADER_COMPONENT_CPP