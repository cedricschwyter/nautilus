#ifndef NAUTILUS_SHADER_GEOMETRY_CPP
#define NAUTILUS_SHADER_GEOMETRY_CPP

#include "NautilusShaderGeometry.hpp"

namespace nautilus {

    NautilusShaderGeometry::NautilusShaderGeometry() {
        m_glShaderType = GL_GEOMETRY_SHADER;
    }

    NautilusShaderGeometry::~NautilusShaderGeometry() {
    }

}

#endif      // NAUTILUS_SHADER_GEOMERY_CPP