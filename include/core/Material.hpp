#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <Texture.hpp>

namespace Kuma3D {

struct Material
{
  Texture mDiffuse;
  Texture mSpecular;
};

} // namespace Kuma3D

#endif
