#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <glad/glad.h>

#include "KumaGL/Renderbuffer.hpp"
#include "KumaGL/Texture.hpp"

namespace KumaGL {
class Framebuffer {
public:
  Framebuffer();
  ~Framebuffer();
  Framebuffer(Framebuffer &&aBuffer);
  Framebuffer &operator=(Framebuffer &&aBuffer);
  Framebuffer(const Framebuffer &aBuffer) = delete;
  Framebuffer &operator=(const Framebuffer &aBuffer) = delete;

  void Bind(GLenum aBufferType = GL_FRAMEBUFFER);

  void AttachTexture(const Texture &aTexture,
                     GLenum aAttachmentType = GL_COLOR_ATTACHMENT0,
                     GLenum aTextureType = GL_TEXTURE_2D);
  void AttachRenderbuffer(const Renderbuffer &aBuffer,
                          GLenum aAttachmentType = GL_DEPTH_STENCIL_ATTACHMENT);

  GLuint GetID() const { return mID; }

private:
  bool mValid{false};

  GLsizei mTextureWidth{0};
  GLsizei mTextureHeight{0};

  GLuint mID{0};
};
} // namespace KumaGL

#endif // !DEBUG
