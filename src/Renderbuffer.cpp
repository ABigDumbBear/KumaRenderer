#include <KumaGL/Renderbuffer.hpp>

namespace KumaGL {
/******************************************************************************/
Renderbuffer::Renderbuffer() {
  glGenRenderbuffers(1, &mID);
  mValid = true;
}

/******************************************************************************/
Renderbuffer::~Renderbuffer() {
  if (mValid) {
    glDeleteRenderbuffers(1, &mID);
    mValid = false;
  }
}

/******************************************************************************/
Renderbuffer::Renderbuffer(Renderbuffer &&aBuffer) {
  mID = aBuffer.GetID();

  aBuffer.mValid = false;
  mValid = true;
}

/******************************************************************************/
Renderbuffer &Renderbuffer::operator=(Renderbuffer &&aBuffer) {
  mID = aBuffer.GetID();

  aBuffer.mValid = false;
  mValid = true;

  return *this;
}

/******************************************************************************/
void Renderbuffer::Bind() const { glBindRenderbuffer(GL_RENDERBUFFER, mID); }

/******************************************************************************/
void Renderbuffer::SetStorageParameters(GLenum aStorageFormat, GLsizei aWidth,
                                        GLsizei aHeight) {
  Bind();
  glRenderbufferStorage(GL_RENDERBUFFER, aStorageFormat, aWidth, aHeight);
}
} // namespace KumaGL
