#ifndef NAUTILUS_SHADER_VERTEX_CPP
#define NAUTILUS_SHADER_VERTEX_CPP

#include "NautilusShaderVertex.hpp"

namespace nautilus {

    NautilusShaderVertex::NautilusShaderVertex() {
        m_glShaderType = GL_VERTEX_SHADER;
    }

    NautilusShaderVertex::~NautilusShaderVertex() {
    }

}

#endif      // NAUTILUS_SHADER_VERTEX_CPP