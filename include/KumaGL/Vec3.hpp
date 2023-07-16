#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <ostream>

namespace KumaGL {
class Vec3 {
public:
  Vec3() : x(0.0), y(0.0), z(0.0) {}
  Vec3(float a, float b, float c) : x(a), y(b), z(c){};

  Vec3 &operator+=(const Vec3 &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return (*this);
  }

  Vec3 &operator-=(const Vec3 &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return (*this);
  }

  Vec3 &operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return (*this);
  }

  Vec3 &operator*=(const Vec3 &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return (*this);
  }

  Vec3 &operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return (*this);
  }

  float x, y, z;
};

/******************************************************************************/
inline std::ostream &operator<<(std::ostream &os, const Vec3 &rhs) {
  os << rhs.x << " " << rhs.y << " " << rhs.z;
  return os;
}

/******************************************************************************/
inline Vec3 operator+(const Vec3 &lhs, const Vec3 &rhs) {
  return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
};

/******************************************************************************/
inline Vec3 operator-(const Vec3 &lhs, const Vec3 &rhs) {
  return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
};

/******************************************************************************/
inline Vec3 operator*(const Vec3 &lhs, float rhs) {
  return Vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

/******************************************************************************/
inline Vec3 operator/(const Vec3 &lhs, float rhs) {
  return Vec3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

/******************************************************************************/
inline Vec3 Normalize(const Vec3 &aVector) {
  auto magnitude = std::sqrt(std::pow(aVector.x, 2) + std::pow(aVector.y, 2) +
                             std::pow(aVector.z, 2));

  Vec3 result(0, 0, 0);
  if (magnitude > 0) {
    result.x = aVector.x / magnitude;
    result.y = aVector.y / magnitude;
    result.z = aVector.z / magnitude;
  }

  return result;
}

/******************************************************************************/
inline Vec3 Cross(const Vec3 &aVectorA, const Vec3 &aVectorB) {
  auto yz = aVectorA.y * aVectorB.z;
  auto zy = aVectorA.z * aVectorB.y;
  auto zx = aVectorA.z * aVectorB.x;
  auto xz = aVectorA.x * aVectorB.z;
  auto xy = aVectorA.x * aVectorB.y;
  auto yx = aVectorA.y * aVectorB.x;

  return Vec3(yz - zy, zx - xz, xy - yx);
}

/******************************************************************************/
inline float Dot(const Vec3 &aVectorA, const Vec3 &aVectorB) {
  auto xx = aVectorA.x * aVectorB.x;
  auto yy = aVectorA.y * aVectorB.y;
  auto zz = aVectorA.z * aVectorB.z;

  return (xx + yy + zz);
}

/******************************************************************************/
inline float Distance(const Vec3 &aVectorA, const Vec3 &aVectorB) {
  auto xVal = aVectorB.x - aVectorA.x;
  auto yVal = aVectorB.y - aVectorA.y;
  auto zVal = aVectorB.z - aVectorA.z;

  return std::sqrt(std::pow(xVal, 2) + std::pow(yVal, 2) + std::pow(zVal, 2));
}
} // namespace KumaGL

#endif // !VEC3_HPP
