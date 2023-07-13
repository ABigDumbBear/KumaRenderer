#include "KumaGL/Framebuffer.hpp"
#include "KumaGL/Renderbuffer.hpp"

namespace KumaGL {

/******************************************************************************/
Framebuffer::Framebuffer() {
  glGenFramebuffers(1, &mID);
  mValid = true;
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
  Bind();
  glFramebufferTexture2D(aBufferType, aAttachmentType, aTextureType,
                         aTexture.GetID(), 0);
}

/******************************************************************************/
void Framebuffer::AttachRenderbuffer(const Renderbuffer &aBuffer,
                                     GLenum aAttachmentType) {
  Bind();
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, aAttachmentType, GL_RENDERBUFFER,
                            aBuffer.GetID());
}

} // namespace KumaGL
