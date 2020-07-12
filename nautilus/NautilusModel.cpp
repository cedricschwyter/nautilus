#ifndef NAUTILUS_MODEL_CPP
#define NAUTILUS_MODEL_CPP

#include "NautilusModel.hpp"

NautilusModel::NautilusModel() {
}

NautilusModel::NautilusModel(const NautilusModel& _other) {
}

NautilusModel& NautilusModel::operator=(const NautilusModel& _other) {
    return *this;
}

glm::mat4 NautilusModel::matrix() {
    return glm::mat4();
}

nautilus::NautilusStatus NautilusModel::bind(NautilusPipeline _pipe) {
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusModel::load(const std::string& _path) {
    Assimp::Importer imp;
    const aiScene* scene = imp.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::string err = imp.GetErrorString();
        nautilus::logger::log("ASSIMP Importer error: " + err);
        return nautilus::NAUTILUS_STATUS_FATAL;
    }
    std::string dir = _path.substr(0, _path.find_last_of("/"));
    m_dir = dir;
    node(scene->mRootNode, scene);
    return nautilus::NAUTILUS_STATUS_OK;
}

nautilus::NautilusStatus NautilusModel::node(aiNode* _node, const aiScene* _scene) {
    for (uint32_t i = 0; i < _node->mNumMeshes; i++) {
        aiMesh* mesh = _scene->mMeshes[_node->mMeshes[i]];
        m_submeshes.push_back(new NautilusMesh(mesh, _scene));
    }
    for (uint32_t i = 0; i < _node->mNumChildren; i++) 
        node(_node->mChildren[i], _scene);
    return nautilus::NAUTILUS_STATUS_OK;
}

NautilusModel::~NautilusModel() {
    for(auto mesh : m_submeshes)
        delete mesh;
}

#endif      // NAUTILUS_MODEL_CPP