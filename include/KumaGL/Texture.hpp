#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <glad/glad.h>

namespace KumaGL {
class Texture {
public:
  Texture();
  ~Texture();
  Texture(Texture &&aTexture);
  Texture &operator=(Texture &&aTexture);
  Texture(const Texture &aTexture) = delete;
  Texture &operator=(const Texture &aTexture) = delete;

  void LoadFromFile(const std::string &aFile, GLint aLoadFormat = GL_RGBA);
  void LoadFromData(unsigned char *aData, GLsizei aWidth, GLsizei aHeight,
                    GLint aLoadFormat = GL_RGBA);

  void Bind() const;

  void GenerateMipmap() const;

  void SetParameter(GLenum aParam, GLint aValue) const;
  void SetParameter(GLenum aParam, GLfloat aValue) const;

  GLsizei GetWidth() const { return mWidth; }
  GLsizei GetHeight() const { return mHeight; }
  GLuint GetID() const { return mID; }

private:
  GLsizei mWidth{0};
  GLsizei mHeight{0};

  GLuint mID{0};

  bool mValid{false};

  static GLuint mBoundTexture;
};
} // namespace KumaGL

#endif // !TEXTURE_HPP
