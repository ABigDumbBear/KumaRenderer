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
  glViewport(0, 0, mTextureWidth, mTextureHeight);
}

/******************************************************************************/
void Framebuffer::AttachTexture(const Texture &aTexture, GLenum aAttachmentType,
                                GLenum aTextureType) {
  mTextureWidth = aTexture.GetWidth();
  mTextureHeight = aTexture.GetHeight();

  glBindFramebuffer(GL_FRAMEBUFFER, mID);
  glFramebufferTexture2D(GL_FRAMEBUFFER, aAttachmentType, aTextureType,
                         aTexture.GetID(), 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/******************************************************************************/
void Framebuffer::AttachRenderbuffer(const Renderbuffer &aBuffer,
                                     GLenum aAttachmentType) {
  glBindFramebuffer(GL_FRAMEBUFFER, mID);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, aAttachmentType, GL_RENDERBUFFER,
                            aBuffer.GetID());
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace KumaGL
