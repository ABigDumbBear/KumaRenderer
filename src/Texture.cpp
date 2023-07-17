#include "KumaGL/Texture.hpp"
#include "KumaGL/GLObject.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace KumaGL {
GLuint Texture::mBoundTexture = 0;

/******************************************************************************/
Texture::Texture() { Generate(); }

/******************************************************************************/
Texture::~Texture() { Delete(); }

/******************************************************************************/
Texture::Texture(Texture &&aTexture) : GLObject(std::move(aTexture)) {
  mWidth = aTexture.mWidth;
  mHeight = aTexture.mHeight;
}

/******************************************************************************/
Texture &Texture::operator=(Texture &&aTexture) {
  GLObject::operator=(std::move(aTexture));
  mWidth = aTexture.mWidth;
  mHeight = aTexture.mHeight;

  return *this;
}

/******************************************************************************/
void Texture::Generate() {
  if (!mID) {
    glGenTextures(1, &mID);
  }
}

/******************************************************************************/
void Texture::Delete() {
  if (mID) {
    glDeleteTextures(1, &mID);
    mID = 0;
  }
}

/******************************************************************************/
void Texture::Bind() const {
  glBindTexture(GL_TEXTURE_2D, mID);
  mBoundTexture = mID;
}

/******************************************************************************/
void Texture::Unbind() const {
  glBindTexture(GL_TEXTURE_2D, 0);
  mBoundTexture = 0;
}

/******************************************************************************/
void Texture::LoadFromFile(const std::string &aFile, GLint aLoadFormat) {
  int channels;
  auto data = stbi_load(aFile.c_str(), &mWidth, &mHeight, &channels, 0);

  LoadFromData(data, mWidth, mHeight, aLoadFormat);

  stbi_image_free(data);
}

/******************************************************************************/
void Texture::LoadFromData(unsigned char *aData, GLsizei aWidth,
                           GLsizei aHeight, GLint aLoadFormat) {
  mWidth = aWidth;
  mHeight = aHeight;

  glBindTexture(GL_TEXTURE_2D, mID);
  glTexImage2D(GL_TEXTURE_2D, 0, aLoadFormat, mWidth, mHeight, 0, aLoadFormat,
               GL_UNSIGNED_BYTE, aData);
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, mBoundTexture);
}

/******************************************************************************/
void Texture::SetParameter(GLenum aParam, GLint aValue) const {
  glBindTexture(GL_TEXTURE_2D, mID);
  glTexParameteri(GL_TEXTURE_2D, aParam, aValue);
  glBindTexture(GL_TEXTURE_2D, mBoundTexture);
}

/******************************************************************************/
void Texture::SetParameter(GLenum aParam, GLfloat aValue) const {
  glBindTexture(GL_TEXTURE_2D, mID);
  glTexParameterf(GL_TEXTURE_2D, aParam, aValue);
  glBindTexture(GL_TEXTURE_2D, mBoundTexture);
}

/******************************************************************************/
void Texture::GenerateMipmap() const {
  glBindTexture(GL_TEXTURE_2D, mID);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, mBoundTexture);
}
} // namespace KumaGL
