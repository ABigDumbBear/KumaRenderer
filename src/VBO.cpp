#include "KumaGL/VBO.hpp"
#include "KumaGL/GLObject.hpp"

#include <algorithm>

namespace KumaGL {
/******************************************************************************/
VBO::VBO() { Generate(); }

/******************************************************************************/
VBO::~VBO() { Delete(); }

/******************************************************************************/
VBO::VBO(VBO &&aBuffer) : GLObject(std::move(aBuffer)) {}

/******************************************************************************/
VBO &VBO::operator=(VBO &&aBuffer) {
  GLObject::operator=(std::move(aBuffer));
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
  if (mID) {
    glDeleteBuffers(1, &mID);
    mID = 0;
  }
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
