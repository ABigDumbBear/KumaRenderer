#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>

#include <assimp/material.h>
#include <assimp/scene.h>

#include "Mesh.hpp"

namespace KumaGL {
class Model {
public:
  Model() = default;
  ~Model() = default;
  Model(Model &&) = default;
  Model &operator=(Model &&) = default;
  Model(const Model &) = delete;
  Model &operator=(const Model &) = delete;

  void LoadFromFile(const std::string &aFile);

  void Delete();

  void Draw(GLenum aMode = GL_TRIANGLES) const;
  void DrawInstanced(int aNumInstances, GLenum aMode = GL_TRIANGLES) const;

  std::vector<Mesh> &GetMeshes() { return mMeshes; }

private:
  void ProcessNode(aiNode &aNode, const aiScene &aScene);
  void ProcessMesh(aiMesh &aMesh, unsigned int aMeshIndex,
                   const aiScene &aScene);

  std::vector<Mesh> mMeshes;
};
} // namespace KumaGL

#endif // !MODEL_HPP
