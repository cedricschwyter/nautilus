#ifndef NAUTILUS_SHADER_COMPONENT_CPP
#define NAUTILUS_SHADER_COMPONENT_CPP

#include "NautilusShaderComponent.hpp"

namespace nautilus {

    NautilusShaderComponent::NautilusShaderComponent() {
    }

    NautilusShaderComponent::~NautilusShaderComponent() {
    }

    NautilusStatus NautilusShaderComponent::name(const std::string& _name) {
        m_name = _name;
        return NAUTILUS_STATUS_OK;
    }

    NautilusStatus NautilusShaderComponent::value(const std::string& _value) {
        m_value = _value;
        return NAUTILUS_STATUS_OK;
    }

}

#endif      // NAUTILUS_SHADER_COMPONENT_CPP