#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>

#include <assimp/material.h>
#include <assimp/scene.h>

#include "Mesh.hpp"
#include "Texture.hpp"

namespace Kuma3D {

class Model
{
  public:
    void LoadFromFile(const std::string& aFile);

  private:
    void ProcessNode(aiNode& aNode,
                     const aiScene& aScene,
                     const std::string& aWorkingDirectory);
    void ProcessMesh(aiMesh& aMesh,
                     const aiScene& aScene,
                     const std::string& aWorkingDirectory);
    std::vector<Texture> GetTexturesForMaterial(const aiMaterial& aMaterial,
                                                aiTextureType aType,
                                                const std::string& aWorkingDirectory);

    std::vector<Mesh> mMeshes;
};

} // namespace Kuma3D

#endif
