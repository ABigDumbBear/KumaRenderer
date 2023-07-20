#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include <glad/glad.h>

#include "VBO.hpp"
#include "Vec3.hpp"

namespace KumaGL {
struct MeshVertex {
  Vec3 mPosition;
  Vec3 mColor;
  Vec3 mNormal;
  float mTexCoords[2]{0.0, 0.0};
};

class Mesh {
public:
  Mesh();
  ~Mesh();
  Mesh(Mesh &&aMesh);
  Mesh &operator=(Mesh &&aMesh);
  Mesh(const Mesh &aMesh) = delete;
  Mesh &operator=(const Mesh &aMesh) = delete;

  void Draw(GLenum aMode = GL_TRIANGLES) const;
  void DrawInstanced(int aNumInstances, GLenum aMode = GL_TRIANGLES) const;

  void UpdateVertices();
  void UpdateIndices();

  void InitQuad();
  void InitCube();

  GLuint GetVertexArrayID() const { return mVertexArray; }

  std::vector<MeshVertex> mVertices;
  std::vector<unsigned int> mIndices;

  VBO mVertexBuffer;
  VBO mInstanceBuffer;
  VBO mCustomBuffer;
  VBO mElementBuffer;

private:
  GLuint mVertexArray{0};

  bool mValid{false};
};
} // namespace KumaGL

#endif // !MESH_HPP
