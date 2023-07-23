#include "KumaGL/Model.hpp"
#include "KumaGL/Vec3.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace KumaGL {
/******************************************************************************/
void Model::LoadFromFile(const std::string &aFile) {
  mMeshes.clear();

  Assimp::Importer importer;
  auto scene =
      importer.ReadFile(aFile, aiProcess_Triangulate | aiProcess_FlipUVs);

  ProcessNode(*scene->mRootNode, *scene);
}

/******************************************************************************/
void Model::Delete() {
  for (auto &mesh : mMeshes) {
    mesh.Delete();
  }
}

/******************************************************************************/
void Model::Draw(GLenum aMode) const {
  for (const auto &mesh : mMeshes) {
    mesh.Draw(aMode);
  }
}

/******************************************************************************/
void Model::DrawInstanced(int aNumInstances, GLenum aMode) const {
  for (const auto &mesh : mMeshes) {
    mesh.DrawInstanced(aNumInstances, aMode);
  }
}

/******************************************************************************/
void Model::ProcessNode(aiNode &aNode, const aiScene &aScene) {
  // Process each mesh in this node.
  for (int i = 0; i < aNode.mNumMeshes; ++i) {
    auto mesh = aScene.mMeshes[aNode.mMeshes[i]];
    ProcessMesh(*mesh, i, aScene);
  }

  // Process each of this node's children.
  for (int i = 0; i < aNode.mNumChildren; ++i) {
    ProcessNode(*aNode.mChildren[i], aScene);
  }
}

/******************************************************************************/
void Model::ProcessMesh(aiMesh &aMesh, unsigned int aMeshIndex,
                        const aiScene &aScene) {
  Mesh mesh;

  // Retrieve the vertex data.
  for (int i = 0; i < aMesh.mNumVertices; ++i) {
    MeshVertex vertex;

    // Retrieve the vertex position.
    if (aMesh.HasPositions()) {
      auto &position = aMesh.mVertices[i];
      vertex.mPosition = Vec3(position.x, position.y, position.z);
    }

    // Retrieve the vertex color (for channel 0).
    if (aMesh.HasVertexColors(0)) {
      auto &color = aMesh.mColors[0][i];
      vertex.mColor = Vec3(color.r, color.g, color.b);
    }

    // Retrieve the vertex normal.
    if (aMesh.HasNormals()) {
      auto &normal = aMesh.mNormals[i];
      vertex.mNormal = Vec3(normal.x, normal.y, normal.z);
    }

    // Retrieve the vertex texture coordinates (for channel 0).
    if (aMesh.HasTextureCoords(0)) {
      auto &texCoords = aMesh.mTextureCoords[0][i];
      vertex.mTexCoords[0] = texCoords.x;
      vertex.mTexCoords[1] = texCoords.y;
    }

    mesh.mVertices.emplace_back(vertex);
  }

  // Retrieve the index data.
  for (int i = 0; i < aMesh.mNumFaces; ++i) {
    auto face = aMesh.mFaces[i];
    for (int j = 0; j < face.mNumIndices; ++j) {
      mesh.mIndices.emplace_back(face.mIndices[j]);
    }
  }

  mesh.UpdateVertices();
  mesh.UpdateIndices();

  mMeshes.emplace_back(std::move(mesh));
}
} // namespace KumaGL
