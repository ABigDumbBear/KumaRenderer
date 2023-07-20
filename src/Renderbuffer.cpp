#include "KumaGL/Renderbuffer.hpp"

namespace KumaGL {
/******************************************************************************/
Renderbuffer::Renderbuffer() { Generate(); }

/******************************************************************************/
Renderbuffer::~Renderbuffer() { Delete(); }

/******************************************************************************/
Renderbuffer::Renderbuffer(Renderbuffer &&aBuffer) {
  mID = aBuffer.mID;
  aBuffer.mID = 0;
}

/******************************************************************************/
Renderbuffer &Renderbuffer::operator=(Renderbuffer &&aBuffer) {
  Delete();
  mID = aBuffer.mID;
  aBuffer.mID = 0;

  return *this;
}

/******************************************************************************/
void Renderbuffer::Generate() {
  if (!mID) {
    glGenRenderbuffers(1, &mID);
  }
}

/******************************************************************************/
void Renderbuffer::Delete() {
  glDeleteRenderbuffers(1, &mID);
  mID = 0;
}

/******************************************************************************/
void Renderbuffer::Bind() { glBindRenderbuffer(GL_RENDERBUFFER, mID); }

/******************************************************************************/
void Renderbuffer::Unbind() { glBindRenderbuffer(GL_RENDERBUFFER, 0); }

/******************************************************************************/
void Renderbuffer::SetStorageParameters(GLenum aStorageFormat, GLsizei aWidth,
                                        GLsizei aHeight) {
  Bind();
  glRenderbufferStorage(GL_RENDERBUFFER, aStorageFormat, aWidth, aHeight);
  Unbind();
}
} // namespace KumaGL
