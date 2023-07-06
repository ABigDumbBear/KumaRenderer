#include "KumaGL/Framebuffer.hpp"

namespace KumaGL {

/******************************************************************************/
Framebuffer::Framebuffer() {
  if (!mValid) {
    glGenFramebuffers(1, &mID);
    mValid = true;
  }
}

/******************************************************************************/
Framebuffer::~Framebuffer() {
  if (mValid) {
    glDeleteFramebuffers(1, &mID);
    mValid = false;
  }
}

/******************************************************************************/
Framebuffer::Framebuffer(Framebuffer &&aBuffer) {
  mID = aBuffer.GetID();

  aBuffer.mValid = false;
  mValid = true;
}

/******************************************************************************/
Framebuffer &Framebuffer::operator=(Framebuffer &&aBuffer) {
  mID = aBuffer.GetID();

  aBuffer.mValid = false;
  mValid = true;

  return *this;
}

/******************************************************************************/
void Framebuffer::Bind(GLenum aBufferType) {
  glBindFramebuffer(aBufferType, mID);
}

/******************************************************************************/
void Framebuffer::AttachTexture(const Texture &aTexture, GLenum aBufferType,
                                GLenum aAttachmentType, GLenum aTextureType) {
  glFramebufferTexture2D(aBufferType, aAttachmentType, aTextureType,
                         aTexture.GetID(), 0);
}

} // namespace KumaGL
