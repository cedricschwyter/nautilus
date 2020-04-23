#ifndef NAUTILUS_MESH_CPP
#define NAUTILUS_MESH_CPP

#include "NautilusMesh.hpp"

namespace nautilus {

    NautilusMesh::NautilusMesh() {
    }

    NautilusMesh::NautilusMesh(aiMesh* _mesh, const aiScene* _scene) {
        std::vector< NautilusVertex >                   vertices;
        std::vector< uint32_t >                         indices;
        std::unordered_map< NautilusVertex, uint32_t >  uniqueVertices         = {};
        for(uint32_t i = 0; i < _mesh->mNumVertices; i++) {
            NautilusVertex vertex = {};
            glm::vec3 vector;
            vector.x = _mesh->mVertices[i].x;
            vector.y = _mesh->mVertices[i].y;
            vector.z = _mesh->mVertices[i].z;
            vertex.m_pos = vector;
            if (_mesh->HasNormals()) {
                vector.x = _mesh->mNormals[i].x;
                vector.y = _mesh->mNormals[i].y;
                vector.z = _mesh->mNormals[i].z;
                vertex.m_nor = vector;
            }
            if(_mesh->mTextureCoords[0]) {
                glm::vec2 vec;
                vec.x = _mesh->mTextureCoords[0][i].x;
                vec.y = _mesh->mTextureCoords[0][i].y;
                vertex.m_tex = vec;
            } else {
                vertex.m_tex = glm::vec2(0.0f, 0.0f);
            }
            if(_mesh->HasTangentsAndBitangents()) {
                vector.x = _mesh->mTangents[i].x;
                vector.y = _mesh->mTangents[i].y;
                vector.z = _mesh->mTangents[i].z;
                vertex.m_tan = vector;
                vector.x = _mesh->mBitangents[i].x;
                vector.y = _mesh->mBitangents[i].y;
                vector.z = _mesh->mBitangents[i].z;
                vertex.m_bit = vector;
            }
            vertices.push_back(vertex);
        }
        for(unsigned int i = 0; i < _mesh->mNumFaces; i++) {
            aiFace face = _mesh->mFaces[i];
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        /**
        std::vector< TextureObject > textures;
        aiMaterial* material = _scene->mMaterials[_mesh->mMaterialIndex];
        std::vector< TextureObject > diffuseMaps = loadASSIMPMaterialTextures(material, aiTextureType_DIFFUSE, TT_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector< TextureObject > specularMaps = loadASSIMPMaterialTextures(material, aiTextureType_SPECULAR, TT_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        std::vector< TextureObject > normalMaps = loadASSIMPMaterialTextures(material, aiTextureType_NORMALS, TT_NORMAL);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        std::vector< TextureObject > heightMaps = loadASSIMPMaterialTextures(material, aiTextureType_HEIGHT, TT_HEIGHT);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());*/
    }

    NautilusMesh::NautilusMesh(const NautilusMesh& _other) {
    }

    NautilusMesh& NautilusMesh::operator=(const NautilusMesh& _other) {
        return *this;
    }

    NautilusMesh::~NautilusMesh() {
    }

}

#endif      // NAUTILUS_MESH_CPP