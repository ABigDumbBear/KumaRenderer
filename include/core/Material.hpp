#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <Texture.hpp>

namespace KumaGL {

struct Material
{
  Texture mDiffuse;
  Texture mSpecular;
};

} // namespace KumaGL

#endif
