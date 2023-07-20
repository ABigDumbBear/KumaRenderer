#include "KumaGL/VBO.hpp"

namespace KumaGL {
/******************************************************************************/
VBO::VBO() { Generate(); }

/******************************************************************************/
VBO::~VBO() { Delete(); }

/******************************************************************************/
VBO::VBO(VBO &&aBuffer) {
  mID = aBuffer.mID;
  aBuffer.mID = 0;
}

/******************************************************************************/
VBO &VBO::operator=(VBO &&aBuffer) {
  Delete();
  mID = aBuffer.mID;
  aBuffer.mID = 0;

  return *this;
}

/******************************************************************************/
void VBO::Generate() {
  if (!mID) {
    glGenBuffers(1, &mID);
  }
}

/******************************************************************************/
void VBO::Delete() {
  glDeleteBuffers(1, &mID);
  mID = 0;
}

/******************************************************************************/
void VBO::Bind(GLenum aTarget) { glBindBuffer(aTarget, mID); }

/******************************************************************************/
void VBO::Unbind(GLenum aTarget) { glBindBuffer(aTarget, 0); }

/******************************************************************************/
void VBO::CopyData(GLenum aTarget, GLsizeiptr aSize, const void *aData,
                   GLenum aUsage) {
  Bind(aTarget);
  glBufferData(aTarget, aSize, aData, aUsage);
  Unbind(aTarget);
}
} // namespace KumaGL
