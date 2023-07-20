#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

#include <string>

namespace KumaGL {
class Texture {
public:
  Texture();
  ~Texture();
  Texture(Texture &&aTexture);
  Texture &operator=(Texture &&aTexture);
  Texture(const Texture &aTexture) = delete;
  Texture &operator=(const Texture &aTexture) = delete;

  void Generate();
  void Delete();
  void Bind();
  void Unbind();

  void LoadFromFile(const std::string &aFile, GLint aLoadFormat = GL_RGBA);
  void LoadFromData(unsigned char *aData, GLsizei aWidth, GLsizei aHeight,
                    GLint aLoadFormat = GL_RGBA);

  void SetParameter(GLenum aParam, GLint aValue);
  void SetParameter(GLenum aParam, GLfloat aValue);
  void GenerateMipmap();

  GLsizei GetWidth() const { return mWidth; }
  GLsizei GetHeight() const { return mHeight; }
  GLuint GetID() const { return mID; }

private:
  GLsizei mWidth{0};
  GLsizei mHeight{0};

  GLuint mID{0};
};
} // namespace KumaGL

#endif // !TEXTURE_HPP
