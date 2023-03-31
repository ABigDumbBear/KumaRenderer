#include "Mesh.hpp"

#include <glad/glad.h>

namespace Kuma3D {

/******************************************************************************/
Mesh::Mesh()
{
  // Generate a VAO and several VBOs for the mesh, then configure them.
  glGenVertexArrays(1, &mVertexArray);
  glGenBuffers(1, &mVertexBuffer);
  glGenBuffers(1, &mInstanceBuffer);
  glGenBuffers(1, &mElementBuffer);

  // Bind the vertex array.
  glBindVertexArray(mVertexArray);

  // Bind the vertex buffer.
  glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

  // Configure the vertex position attribute.
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(MeshVertex),
                        (void*)(0));

  // Configure the vertex color attribute.
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(MeshVertex),
                        (void*)(offsetof(MeshVertex, mColor)));

  // Configure the vertex normal attribute.
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(MeshVertex),
                        (void*)(offsetof(MeshVertex, mNormal)));

  // Configure the vertex texture coordinate attribute.
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(MeshVertex),
                        (void*)(offsetof(MeshVertex, mTexCoords)));

  // Bind the instance buffer.
  glBindBuffer(GL_ARRAY_BUFFER, mInstanceBuffer);

  // Configure the instance attributes.
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4,
                        4,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Mat4),
                        (void*)0);
  glEnableVertexAttribArray(5);
  glVertexAttribPointer(5,
                        4,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Mat4),
                        (void*)(4 * sizeof(float)));
  glEnableVertexAttribArray(6);
  glVertexAttribPointer(6,
                        4,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Mat4),
                        (void*)(8 * sizeof(float)));
  glEnableVertexAttribArray(7);
  glVertexAttribPointer(7,
                        4,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Mat4),
                        (void*)(12 * sizeof(float)));

  glVertexAttribDivisor(4, 1);
  glVertexAttribDivisor(5, 1);
  glVertexAttribDivisor(6, 1);
  glVertexAttribDivisor(7, 1);

  // Bind the element buffer.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBuffer);

  // Unbind the vertex array.
  glBindVertexArray(0);
}

/******************************************************************************/
Mesh::~Mesh()
{
  glDeleteVertexArrays(1, &mVertexArray);
  glDeleteBuffers(1, &mVertexBuffer);
  glDeleteBuffers(1, &mInstanceBuffer);
  glDeleteBuffers(1, &mElementBuffer);
}

/******************************************************************************/
void Mesh::Draw(const Shader& aShader)
{
  glBindVertexArray(mVertexArray);

  // Draw the mesh.
  aShader.Activate();
  glDrawElements(static_cast<GLenum>(mRenderMode),
                 mIndices.size(),
                 GL_UNSIGNED_INT,
                 0);

  glBindVertexArray(0);
}

/******************************************************************************/
void Mesh::DrawInstanced(const Shader& aShader,
                         int aNumInstances,
                         const std::vector<Mat4>& aMatrices)
{
  glBindVertexArray(mVertexArray);

  // Copy data into the instance buffer.
  glBindBuffer(GL_ARRAY_BUFFER, mInstanceBuffer);
  glBufferData(GL_ARRAY_BUFFER, aMatrices.size() * sizeof(Mat4), &aMatrices[0], GL_DYNAMIC_DRAW);

  // Draw the mesh.
  aShader.Activate();
  glDrawElementsInstanced(static_cast<GLenum>(mRenderMode),
                          mIndices.size(),
                          GL_UNSIGNED_INT,
                          0,
                          aNumInstances);

  glBindVertexArray(0);
}

/******************************************************************************/
void Mesh::AddVertex(const MeshVertex& aVertex)
{
  mVertices.emplace_back(aVertex);

  glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
  glBufferData(GL_ARRAY_BUFFER,
               mVertices.size() * sizeof(MeshVertex),
               &mVertices[0],
               GL_STATIC_DRAW);
}

/******************************************************************************/
void Mesh::AddIndex(unsigned int aIndex)
{
  mIndices.emplace_back(aIndex);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               mIndices.size() * sizeof(unsigned int),
               &mIndices[0],
               GL_STATIC_DRAW);
}

} // namespace Kuma3D
