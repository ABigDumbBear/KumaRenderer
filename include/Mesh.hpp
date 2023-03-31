#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "Vec3.hpp"

#include "Shader.hpp"
#include "Texture.hpp"

#include "Mat4.hpp"

namespace Kuma3D {

enum class RenderMode
{
  ePOINTS     = 0x0000,
  eLINES      = 0x0001,
  eLINE_LOOP  = 0x0002,
  eLINE_STRIP = 0x0003,
  eTRIANGLES  = 0x0004
};

enum class Projection
{
  ePERSPECTIVE,
  eORTHOGRAPHIC
};

struct MeshVertex
{
  Vec3 mPosition; // location = 0
  Vec3 mColor; // location = 1
  Vec3 mNormal; // location = 2
  float mTexCoords[2] { 0.0, 0.0 }; // location = 3
};

class Mesh
{
  public:
    Mesh();
    ~Mesh();

    void Draw(const Shader& aShader);
    void DrawInstanced(const Shader& aShader,
                       int aNumInstances,
                       const std::vector<Mat4>& aMatrices);

    void AddVertex(const MeshVertex& aVertex);
    void AddIndex(unsigned int aIndex);

    RenderMode mRenderMode { RenderMode::eTRIANGLES };
    Projection mProjection { Projection::ePERSPECTIVE };

  private:
    std::vector<MeshVertex> mVertices;
    std::vector<unsigned int> mIndices;

    unsigned int mVertexArray { 0 };
    unsigned int mVertexBuffer { 0 };
    unsigned int mInstanceBuffer { 0 };
    unsigned int mElementBuffer { 0 };
};

} // namespace Kuma3D

#endif
