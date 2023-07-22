#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include "GLObject.hpp"

namespace KumaGL {
class Texture : public GLObject {
public:
  Texture();
  ~Texture();
  Texture(Texture &&aTexture);
  Texture &operator=(Texture &&aTexture);
  Texture(const Texture &aTexture) = delete;
  Texture &operator=(const Texture &aTexture) = delete;

  void Generate();
  void Delete();
  void Bind() const;
  void Unbind() const;

  void LoadFromFile(const std::string &aFile, GLint aLoadFormat = GL_RGBA);
  void LoadFromData(unsigned char *aData, GLsizei aWidth, GLsizei aHeight,
                    GLint aLoadFormat = GL_RGBA);
  void AddSubData(GLint aLevel, GLint aXOffset, GLint aYOffset, GLsizei aWidth,
                  GLsizei aHeight, GLenum aFormat, GLenum aType,
                  const void *aData);

  void SetParameter(GLenum aParam, GLint aValue) const;
  void SetParameter(GLenum aParam, GLfloat aValue) const;
  void GenerateMipmap() const;

  GLsizei GetWidth() const { return mWidth; }
  GLsizei GetHeight() const { return mHeight; }

private:
  GLsizei mWidth{0};
  GLsizei mHeight{0};
};
} // namespace KumaGL

#endif // !TEXTURE_HPP
