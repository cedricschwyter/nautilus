#ifndef NAUTILUS_MESH_HPP
#define NAUTILUS_MESH_HPP

#include "NautilusVertex.hpp"

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <unordered_map>

class NautilusMesh {
public:

    /**
     * Default constructor
     */
    NautilusMesh(void); 

    /**
     * Constructor with arguments
     * @param _mesh The ASSIMP mesh object
     * @param _scene The ASSIMP scene object
     */ 
    NautilusMesh(aiMesh* _mesh, const aiScene* _scene);

    /**
     * Copy constructor
     * @param _other The other instance
     */ 
    NautilusMesh(const NautilusMesh& _other);

    /**
     * Assignment operator
     * @param _other The other instance
     * @return Returns a NautilusMesh reference
     */ 
    NautilusMesh& operator=(const NautilusMesh& _other);

    /**
     * Default destructor
     */
     ~NautilusMesh(void);

private:

protected:

};

#endif      // NAUTILUS_MESH_HPP