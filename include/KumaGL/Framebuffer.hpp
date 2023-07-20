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

  void Generate();
  void Delete();
  void Bind(GLenum aTarget = GL_FRAMEBUFFER);
  void Unbind(GLenum aTarget = GL_FRAMEBUFFER);

  void AttachTexture(const Texture &aTexture, GLenum aTarget = GL_FRAMEBUFFER,
                     GLenum aAttachmentType = GL_COLOR_ATTACHMENT0,
                     GLenum aTextureType = GL_TEXTURE_2D);
  void AttachRenderbuffer(const Renderbuffer &aBuffer,
                          GLenum aTarget = GL_FRAMEBUFFER,
                          GLenum aAttachmentType = GL_DEPTH_STENCIL_ATTACHMENT);

  GLuint GetID() const { return mID; }

private:
  GLuint mID{0};
};
} // namespace KumaGL

#endif // !FRAMEBUFFER_HPP
