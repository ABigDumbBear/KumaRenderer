#ifndef MAT4_HPP
#define MAT4_HPP

#include <ostream>

#include "Vec3.hpp"

namespace KumaGL {
class Mat4 {
public:
  Mat4() {
    data[0][0] = 1.0;
    data[1][0] = 0.0;
    data[2][0] = 0.0;
    data[3][0] = 0.0;
    data[0][1] = 0.0;
    data[1][1] = 1.0;
    data[2][1] = 0.0;
    data[3][1] = 0.0;
    data[0][2] = 0.0;
    data[1][2] = 0.0;
    data[2][2] = 1.0;
    data[3][2] = 0.0;
    data[0][3] = 0.0;
    data[1][3] = 0.0;
    data[2][3] = 0.0;
    data[3][3] = 1.0;
  };

  Mat4(float n00, float n10, float n20, float n30, float n01, float n11,
       float n21, float n31, float n02, float n12, float n22, float n32,
       float n03, float n13, float n23, float n33) {
    data[0][0] = n00;
    data[1][0] = n10;
    data[2][0] = n20;
    data[3][0] = n30;
    data[0][1] = n01;
    data[1][1] = n11;
    data[2][1] = n21;
    data[3][1] = n31;
    data[0][2] = n02;
    data[1][2] = n12;
    data[2][2] = n22;
    data[3][2] = n32;
    data[0][3] = n03;
    data[1][3] = n13;
    data[2][3] = n23;
    data[3][3] = n33;
  };

  float &operator()(unsigned int c, unsigned int r) { return data[c][r]; };

  const float &operator()(unsigned int c, unsigned int r) const {
    return data[c][r];
  };

  float data[4][4];
};

/******************************************************************************/
inline std::ostream &operator<<(std::ostream &os, const Mat4 &rhs) {
  for (int r = 0; r < 4; ++r) {
    for (int c = 0; c < 4; ++c) {
      os << rhs(c, r) << " ";
    }
    os << "\n";
  }

  return os;
}

/******************************************************************************/
inline Mat4 operator*(const Mat4 &lhs, const Mat4 &rhs) {
  return Mat4(lhs(0, 0) * rhs(0, 0) + lhs(1, 0) * rhs(0, 1) +
                  lhs(2, 0) * rhs(0, 2) + lhs(3, 0) * rhs(0, 3),
              lhs(0, 0) * rhs(1, 0) + lhs(1, 0) * rhs(1, 1) +
                  lhs(2, 0) * rhs(1, 2) + lhs(3, 0) * rhs(1, 3),
              lhs(0, 0) * rhs(2, 0) + lhs(1, 0) * rhs(2, 1) +
                  lhs(2, 0) * rhs(2, 2) + lhs(3, 0) * rhs(2, 3),
              lhs(0, 0) * rhs(3, 0) + lhs(1, 0) * rhs(3, 1) +
                  lhs(2, 0) * rhs(3, 2) + lhs(3, 0) * rhs(3, 3),
              lhs(0, 1) * rhs(0, 0) + lhs(1, 1) * rhs(0, 1) +
                  lhs(2, 1) * rhs(0, 2) + lhs(3, 1) * rhs(0, 3),
              lhs(0, 1) * rhs(1, 0) + lhs(1, 1) * rhs(1, 1) +
                  lhs(2, 1) * rhs(1, 2) + lhs(3, 1) * rhs(1, 3),
              lhs(0, 1) * rhs(2, 0) + lhs(1, 1) * rhs(2, 1) +
                  lhs(2, 1) * rhs(2, 2) + lhs(3, 1) * rhs(2, 3),
              lhs(0, 1) * rhs(3, 0) + lhs(1, 1) * rhs(3, 1) +
                  lhs(2, 1) * rhs(3, 2) + lhs(3, 1) * rhs(3, 3),
              lhs(0, 2) * rhs(0, 0) + lhs(1, 2) * rhs(0, 1) +
                  lhs(2, 2) * rhs(0, 2) + lhs(3, 2) * rhs(0, 3),
              lhs(0, 2) * rhs(1, 0) + lhs(1, 2) * rhs(1, 1) +
                  lhs(2, 2) * rhs(1, 2) + lhs(3, 2) * rhs(1, 3),
              lhs(0, 2) * rhs(2, 0) + lhs(1, 2) * rhs(2, 1) +
                  lhs(2, 2) * rhs(2, 2) + lhs(3, 2) * rhs(2, 3),
              lhs(0, 2) * rhs(3, 0) + lhs(1, 2) * rhs(3, 1) +
                  lhs(2, 2) * rhs(3, 2) + lhs(3, 2) * rhs(3, 3),
              lhs(0, 3) * rhs(0, 0) + lhs(1, 3) * rhs(0, 1) +
                  lhs(2, 3) * rhs(0, 2) + lhs(3, 3) * rhs(0, 3),
              lhs(0, 3) * rhs(1, 0) + lhs(1, 3) * rhs(1, 1) +
                  lhs(2, 3) * rhs(1, 2) + lhs(3, 3) * rhs(1, 3),
              lhs(0, 3) * rhs(2, 0) + lhs(1, 3) * rhs(2, 1) +
                  lhs(2, 3) * rhs(2, 2) + lhs(3, 3) * rhs(2, 3),
              lhs(0, 3) * rhs(3, 0) + lhs(1, 3) * rhs(3, 1) +
                  lhs(2, 3) * rhs(3, 2) + lhs(3, 3) * rhs(3, 3));
};

/******************************************************************************/
inline Vec3 operator*(const Mat4 &lhs, const Vec3 &rhs) {
  // This operation assumes a w-coordinate of 1.0.
  return Vec3(lhs(0, 0) * rhs.x + lhs(1, 0) * rhs.y + lhs(2, 0) * rhs.z +
                  lhs(3, 0) * 1.0,
              lhs(0, 1) * rhs.x + lhs(1, 1) * rhs.y + lhs(2, 1) * rhs.z +
                  lhs(3, 1) * 1.0,
              lhs(0, 2) * rhs.x + lhs(1, 2) * rhs.y + lhs(2, 2) * rhs.z +
                  lhs(3, 2) * 1.0);
};

/******************************************************************************/
inline Mat4 Scale(const Vec3 &aVector) {
  return Mat4(aVector.x, 0.0, 0.0, 0.0, 0.0, aVector.y, 0.0, 0.0, 0.0, 0.0,
              aVector.z, 0.0, 0.0, 0.0, 0.0, 1.0);
}

/******************************************************************************/
inline Mat4 Translate(const Vec3 &aVector) {
  return Mat4(1.0, 0.0, 0.0, aVector.x, 0.0, 1.0, 0.0, aVector.y, 0.0, 0.0, 1.0,
              aVector.z, 0.0, 0.0, 0.0, 1.0);
}

/******************************************************************************/
inline Mat4 Rotate(const Vec3 &aVector, float aDegrees) {
  float c = std::cos(aDegrees * (M_PI / 180.0));
  float s = std::sin(aDegrees * (M_PI / 180.0));
  float d = 1.0 - c;

  float vx = aVector.x;
  float vy = aVector.y;
  float vz = aVector.z;

  float vx2 = std::pow(vx, 2) * d;
  float vy2 = std::pow(vy, 2) * d;
  float vz2 = std::pow(vz, 2) * d;

  float vxvy = (vx * vy) * d;
  float vxvz = (vx * vz) * d;
  float vyvz = (vy * vz) * d;

  return Mat4(c + vx2, vxvy - s * vz, vxvz + s * vy, 0.0, vxvy + s * vz,
              c + vy2, vyvz - s * vx, 0.0, vxvz - s * vy, vyvz + s * vx,
              c + vz2, 0.0, 0.0, 0.0, 0.0, 1.0);
}

/******************************************************************************/
inline Mat4 View(const Vec3 &aDirectionVector, const Vec3 &aRightVector,
                 const Vec3 &aPosition) {
  auto upVector = Cross(aDirectionVector, aRightVector);
  Mat4 axesMatrix =
      Mat4(aRightVector.x, aRightVector.y, aRightVector.z, 0.0, upVector.x,
           upVector.y, upVector.z, 0.0, aDirectionVector.x, aDirectionVector.y,
           aDirectionVector.z, 0.0, 0.0, 0.0, 0.0, 1.0);
  Mat4 translationMatrix =
      Mat4(1.0, 0.0, 0.0, -aPosition.x, 0.0, 1.0, 0.0, -aPosition.y, 0.0, 0.0,
           1.0, -aPosition.z, 0.0, 0.0, 0.0, 1.0);

  return axesMatrix * translationMatrix;
}

/******************************************************************************/
inline Mat4 Perspective(float aFOV, float aViewportWidth, float aViewportHeight,
                        float aNearPlane, float aFarPlane) {
  auto rad = aFOV * (M_PI / 180.0);
  auto f = 1.0 / std::tan(rad * 0.5);
  auto aspect = aViewportWidth / aViewportHeight;
  auto far = aFarPlane;
  auto near = aNearPlane;

  return Mat4(f / aspect, 0.0, 0.0, 0.0, 0.0, f, 0.0, 0.0, 0.0, 0.0,
              (near + far) / (near - far), (2 * far * near) / (near - far), 0.0,
              0.0, -1.0, 0.0);
}

/******************************************************************************/
inline Mat4 Orthographic(float aLeft, float aRight, float aBottom, float aTop,
                         float aNear, float aFar) {
  auto rl = 2.0 / (aRight - aLeft);
  auto tb = 2.0 / (aTop - aBottom);
  // auto fn = -2.0 / (aFar - aNear);
  auto fn = 1.0 / (aFar - aNear);
  auto rl2 = ((aRight + aLeft) / (aRight - aLeft)) * -1.0;
  auto tb2 = ((aTop + aBottom) / (aTop - aBottom)) * -1.0;
  // auto fn2 = ((aFar + aNear) / (aFar - aNear)) * -1.0;
  auto fn2 = -aNear / (aFar - aNear);

  return Mat4(rl, 0, 0, rl2, 0, tb, 0, tb2, 0, 0, fn, fn2, 0, 0, 0, 1);
}
} // namespace KumaGL

#endif // !MAT4_HPP
