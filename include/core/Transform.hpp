#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Mat4.hpp"
#include "Vec3.hpp"

#include "MathUtil.hpp"

namespace Kuma3D {

class Transform
{
  public:
    void Translate(const Kuma3D::Vec3& aPos)
    {
      mPosition += aPos;
      UpdateMatrix();
    }

    void Rotate(float x, float y, float z)
    {
      mRotation = mRotation * Kuma3D::Rotate(Vec3(1, 0, 0), x);
      mRotation = mRotation * Kuma3D::Rotate(Vec3(0, 1, 0), y);
      mRotation = mRotation * Kuma3D::Rotate(Vec3(0, 0, 1), z);
      UpdateMatrix();
    }

    void Rotate(const Kuma3D::Vec3& aAxis, float aDegrees)
    {
      mRotation = mRotation * Kuma3D::Rotate(aAxis, aDegrees);
      UpdateMatrix();
    }

    void Scale(float x, float y, float z)
    {
      mScalar *= Vec3(x, y, z);
      UpdateMatrix();
    }

    void SetPosition(const Vec3& aPos)
    {
      mPosition = aPos;
      UpdateMatrix();
    }

    void SetRotation(float x, float y, float z)
    {
      mRotation = Kuma3D::Rotate(Vec3(1, 0, 0), x);
      mRotation = mRotation * Kuma3D::Rotate(Vec3(0, 1, 0), y);
      mRotation = mRotation * Kuma3D::Rotate(Vec3(0, 0, 1), z);
      UpdateMatrix();
    }

    void SetRotation(const Kuma3D::Vec3& aAxis, float aDegrees)
    {
      mRotation = Kuma3D::Rotate(aAxis, aDegrees);
      UpdateMatrix();
    }

    void SetScale(float x, float y, float z)
    {
      mScalar = Vec3(x, y, z);
      UpdateMatrix();
    }

    const Vec3& GetPosition() const { return mPosition; }
    const Mat4& GetRotation() const { return mRotation; }
    const Vec3& GetScalar() const { return mScalar; }

    const Mat4& GetMatrix() const { return mMatrix; }

  private:
    void UpdateMatrix()
    {
      mMatrix = Kuma3D::Translate(mPosition);
      mMatrix = mMatrix * mRotation;
      mMatrix = mMatrix * Kuma3D::Scale(mScalar);
    }

    Vec3 mPosition;
    Mat4 mRotation;
    Vec3 mScalar { 1, 1, 1 };

    Mat4 mMatrix;
};

/*struct Transform
{
  Vec3 mPosition;
  Mat4 mRotation;
  Vec3 mScalar { 1.0, 1.0, 1.0 };

  Entity mParent;
  bool mUseParent { false };
};*/

} // namespace Kuma3D

#endif
