#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Vec3.hpp"

namespace Kuma3D {

struct Light
{
  Vec3 mColor { 1, 1, 1 };

  float mAmbientIntensity { 1 };
  float mDiffuseIntensity { 1 };
  float mSpecularIntensity { 1 };
};

} // namespace Kuma3D

#endif
