#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Shader.hpp"
#include "Texture.hpp"

namespace KumaGL {

struct Material {
  Shader mShader;

  Texture mDiffuse;
  Texture mSpecular;
};

/******************************************************************************/
inline bool operator<(const Material &lhs, const Material &rhs) {
  return lhs.mShader.GetID() < rhs.mShader.GetID() &&
         lhs.mDiffuse.GetID() < rhs.mDiffuse.GetID() &&
         lhs.mSpecular.GetID() < rhs.mSpecular.GetID();
}

} // namespace KumaGL

#endif // !MATERIAL_HPP
