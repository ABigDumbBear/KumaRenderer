#include "KumaGL/Mat4.hpp"

namespace KumaGL {
/******************************************************************************/
Mat4::Mat4() { Identity(); }

/******************************************************************************/
Mat4::Mat4(float n00, float n10, float n20, float n30, float n01, float n11,
           float n21, float n31, float n02, float n12, float n22, float n32,
           float n03, float n13, float n23, float n33) {

  mData[0][0] = n00;
  mData[1][0] = n10;
  mData[2][0] = n20;
  mData[3][0] = n30;
  mData[0][1] = n01;
  mData[1][1] = n11;
  mData[2][1] = n21;
  mData[3][1] = n31;
  mData[0][2] = n02;
  mData[1][2] = n12;
  mData[2][2] = n22;
  mData[3][2] = n32;
  mData[0][3] = n03;
  mData[1][3] = n13;
  mData[2][3] = n23;
  mData[3][3] = n33;
}

/******************************************************************************/
std::ostream &Mat4::operator<<(std::ostream &os) const {
  for (int r = 0; r < 4; ++r) {
    for (int c = 0; c < 4; ++c) {
      os << mData[c][r] << " ";
    }
    os << "\n";
  }

  return os;
}

/******************************************************************************/
void Mat4::operator*=(const Mat4 &rhs) {}

/******************************************************************************/
void Mat4::Identity() {
  mData[0][0] = 1.0;
  mData[1][0] = 0.0;
  mData[2][0] = 0.0;
  mData[3][0] = 0.0;
  mData[0][1] = 0.0;
  mData[1][1] = 1.0;
  mData[2][1] = 0.0;
  mData[3][1] = 0.0;
  mData[0][2] = 0.0;
  mData[1][2] = 0.0;
  mData[2][2] = 1.0;
  mData[3][2] = 0.0;
  mData[0][3] = 0.0;
  mData[1][3] = 0.0;
  mData[2][3] = 0.0;
  mData[3][3] = 1.0;
}

/******************************************************************************/
void Mat4::Scale(float x, float y, float z) {
  Mat4 mat(x, 0.0, 0.0, 0.0, 0.0, y, 0.0, 0.0, 0.0, 0.0, z, 0.0, 0.0, 0.0, 0.0,
           1.0);
}

/******************************************************************************/
void Mat4::Scale(const KumaGL::Vec3 &aVec) { Scale(aVec.x, aVec.y, aVec.z); }

/******************************************************************************/
void Mat4::Translate(float x, float y, float z) {}

/******************************************************************************/
void Mat4::Translate(const KumaGL::Vec3 &aVec) {}

/******************************************************************************/
void Mat4::Rotate(float x, float y, float z) {}

/******************************************************************************/
void Mat4::Rotate(const KumaGL::Vec3 &aVec) {}

/******************************************************************************/
void Mat4::Rotate(const KumaGL::Vec3 &aAxis, float aDegrees) {}

/******************************************************************************/
void Mat4::LookAt(const KumaGL::Vec3 &aPos, const KumaGL::Vec3 &aTarget,
                  const KumaGL::Vec3 &aUp) {}

/******************************************************************************/
void Mat4::Perspective(float aFOV, float aViewportWidth, float aViewportHeight,
                       float aNearPlane, float aFarPlane) {}

/******************************************************************************/
void Mat4::Orthographic(float aLeft, float aRight, float aBottom, float aTop,
                        float aNear, float aFar) {}
} // namespace KumaGL
