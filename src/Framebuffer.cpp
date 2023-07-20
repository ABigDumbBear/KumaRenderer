#include "KumaGL/Framebuffer.hpp"

#include "KumaGL/Renderbuffer.hpp"

namespace KumaGL {
/******************************************************************************/
Framebuffer::Framebuffer() { Generate(); }

/******************************************************************************/
Framebuffer::~Framebuffer() { Delete(); }

/******************************************************************************/
Framebuffer::Framebuffer(Framebuffer &&aBuffer) {
  mID = aBuffer.mID;
  aBuffer.mID = 0;
}

/******************************************************************************/
Framebuffer &Framebuffer::operator=(Framebuffer &&aBuffer) {
  Delete();
  mID = aBuffer.mID;
  aBuffer.mID = 0;

  return *this;
}

/******************************************************************************/
void Framebuffer::Generate() {
  if (!mID) {
    glGenFramebuffers(1, &mID);
  }
}

/******************************************************************************/
void Framebuffer::Delete() {
  glDeleteFramebuffers(1, &mID);
  mID = 0;
}

/******************************************************************************/
void Framebuffer::Bind(GLenum aTarget) { glBindFramebuffer(aTarget, mID); }

/******************************************************************************/
void Framebuffer::Unbind(GLenum aTarget) { glBindFramebuffer(aTarget, 0); }

/******************************************************************************/
void Framebuffer::AttachTexture(const Texture &aTexture, GLenum aTarget,
                                GLenum aAttachmentType, GLenum aTextureType) {
  Bind(aTarget);
  glFramebufferTexture2D(GL_FRAMEBUFFER, aAttachmentType, aTextureType,
                         aTexture.GetID(), 0);
  Unbind(aTarget);
}

/******************************************************************************/
void Framebuffer::AttachRenderbuffer(const Renderbuffer &aBuffer,
                                     GLenum aTarget, GLenum aAttachmentType) {
  Bind(aTarget);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, aAttachmentType, GL_RENDERBUFFER,
                            aBuffer.GetID());
  Unbind(aTarget);
}
} // namespace KumaGL
