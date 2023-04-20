#include "Model.hpp"

#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace Kuma3D {

/******************************************************************************/
void Model::LoadFromFile(const std::string& aFile)
{
  auto workingDirectory = aFile.substr(0, aFile.find_last_of("/\\"));

  Assimp::Importer importer;
  auto scene = importer.ReadFile(aFile,
                                 aiProcess_Triangulate | aiProcess_FlipUVs);
  ProcessNode(*scene->mRootNode, *scene, workingDirectory);
}

/******************************************************************************/
void Model::Draw(const Shader& aShader, GLenum aMode) const
{
  for(const auto& mesh : mMeshes)
  {
    mesh.Draw(aShader, aMode);
  }
}

/******************************************************************************/
void Model::DrawInstanced(const Shader& aShader, int aNumInstances, GLenum aMode) const
{
  for(const auto& mesh : mMeshes)
  {
    mesh.DrawInstanced(aShader, aNumInstances, aMode);
  }
}

/******************************************************************************/
void Model::ProcessNode(aiNode& aNode,
                        const aiScene& aScene,
                        const std::string& aWorkingDirectory)
{
  // Process each mesh in this node.
  for(int i = 0; i < aNode.mNumMeshes; ++i)
  {
    auto mesh = aScene.mMeshes[aNode.mMeshes[i]];
    ProcessMesh(*mesh, aScene, aWorkingDirectory);
  }

  // Process each of this node's children.
  for(int i = 0; i < aNode.mNumChildren; ++i)
  {
    ProcessNode(*aNode.mChildren[i], aScene, aWorkingDirectory);
  }
}

/******************************************************************************/
void Model::ProcessMesh(aiMesh& aMesh,
                        const aiScene& aScene,
                        const std::string& aWorkingDirectory)
{
  Mesh mesh;

  // Retrieve the vertex data.
  for(int i = 0; i < aMesh.mNumVertices; ++i)
  {
    MeshVertex vertex;

    // Default the vertex color to white.
    vertex.mColor = Vec3(1.0, 1.0, 1.0);

    // Retrieve the position data.
    vertex.mPosition = Vec3(aMesh.mVertices[i].x,
                            aMesh.mVertices[i].y,
                            aMesh.mVertices[i].z);

    // Retrieve the texture coordinates.
    // TODO: for now, this only retrieves the texture coordinates for the first
    // texture, since MeshVertex only supports one set of coordinates. It might
    // be worth addressing this in the future.
    auto texCoords = aMesh.mTextureCoords[0];
    if(texCoords != nullptr)
    {
      vertex.mTexCoords[0] = texCoords[i].x;
      vertex.mTexCoords[1] = texCoords[i].y;
    }

    // Load the textures themselves, if there are any.
    if(aMesh.mMaterialIndex >= 0)
    {
      auto material = aScene.mMaterials[aMesh.mMaterialIndex];

      // Load each texture of each type for the material.
      auto textures = GetTexturesForMaterial(*material, aiTextureType_NONE, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
      textures = GetTexturesForMaterial(*material, aiTextureType_DIFFUSE, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
      textures = GetTexturesForMaterial(*material, aiTextureType_SPECULAR, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
      textures = GetTexturesForMaterial(*material, aiTextureType_AMBIENT, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
      textures = GetTexturesForMaterial(*material, aiTextureType_EMISSIVE, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
      textures = GetTexturesForMaterial(*material, aiTextureType_HEIGHT, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
      textures = GetTexturesForMaterial(*material, aiTextureType_NORMALS, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
      textures = GetTexturesForMaterial(*material, aiTextureType_SHININESS, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
      textures = GetTexturesForMaterial(*material, aiTextureType_OPACITY, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
      textures = GetTexturesForMaterial(*material, aiTextureType_DISPLACEMENT, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
      textures = GetTexturesForMaterial(*material, aiTextureType_LIGHTMAP, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
      textures = GetTexturesForMaterial(*material, aiTextureType_REFLECTION, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
      textures = GetTexturesForMaterial(*material, aiTextureType_UNKNOWN, aWorkingDirectory);
      for(const auto& texture : textures)
      {
        //mesh.AddTexture(texture);
      }
    }

    mesh.mVertices.emplace_back(vertex);
  }

  // Retrieve the index data.
  for(int i = 0; i < aMesh.mNumFaces; ++i)
  {
    auto face = aMesh.mFaces[i];
    for(int j = 0; j < face.mNumIndices; ++j)
    {
      mesh.mIndices.emplace_back(face.mIndices[j]);
    }
  }

  mesh.UpdateVertices();
  mesh.UpdateIndices();
  mMeshes.emplace_back(mesh);
}

/******************************************************************************/
std::vector<Texture> Model::GetTexturesForMaterial(const aiMaterial& aMaterial,
                                                   aiTextureType aType,
                                                   const std::string& aWorkingDirectory)
{
  std::vector<Texture> textures;

  for(int i = 0; i < aMaterial.GetTextureCount(aType); ++i)
  {
    aiString str;
    aMaterial.GetTexture(aType, i, &str);

    std::stringstream texturePath;
    texturePath << aWorkingDirectory << "/" << str.C_Str();

    Texture texture;
    texture.LoadFromFile(texturePath.str());
    textures.emplace_back(texture);
  }

  return textures;
}

} // namespace Kuma3D
