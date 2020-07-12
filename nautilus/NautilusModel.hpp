#ifndef NAUTILUS_MODEL_HPP
#define NAUTILUS_MODEL_HPP

#include "NautilusMesh.hpp"
#include "NautilusStatus.hpp"
#include "NautilusPipeline.hpp"
#include "NautilusLogger.hpp"

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

class NautilusModel {
public:

    /**
     * Default constructor
     */
    NautilusModel(void);

    /**
     * Copy constructor
     * @param _other The other instance
     */ 
    NautilusModel(const NautilusModel& _other);

    /**
     * Assignment operator
     * @param _other The other instance
     * @return Returns a NautilusMesh reference
     */ 
    NautilusModel& operator=(const NautilusModel& _other);

    /**
     * Computes the model matrix
     * Can and shall be overridden by derived classes
     * @return Returns a glm::mat4 representing the model matrix
     */ 
    virtual glm::mat4 matrix(void);

    /**
     * Binds the model
     * @param _pipe The pipeline to bind the model to
     * @return
     */ 
    nautilus::NautilusStatus bind(NautilusPipeline _pipe);

    /**
     * Default destructor
     */ 
    ~NautilusModel(void); 

private:

protected:

    std::vector< NautilusMesh* >        m_submeshes;
    std::string                         m_dir;

    /**
     * Loads a model using the ASSIMP model loader
     * @param _path
     * @return Returns a NautilusStatus status code
     */
    nautilus::NautilusStatus load(const std::string& _path); 

    /**
     * Loads an ASSIMP node recursively
     * @param _node The node to load
     * @param _scene The scene object to load into
     * @return Returns a NautilusStatus status code
     */ 
    nautilus::NautilusStatus node(aiNode* _node, const aiScene* _scene);

};

#endif      // NAUTILUS_MODEL_HPP