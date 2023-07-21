#include "KumaGL/Texture.hpp"
#include "KumaGL/GLObject.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace KumaGL {
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
  Delete();
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
void Texture::Bind() { glBindTexture(GL_TEXTURE_2D, mID); }

/******************************************************************************/
void Texture::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

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

  Bind();
  glTexImage2D(GL_TEXTURE_2D, 0, aLoadFormat, mWidth, mHeight, 0, aLoadFormat,
               GL_UNSIGNED_BYTE, aData);
  Unbind();
}

/******************************************************************************/
void Texture::SetParameter(GLenum aParam, GLint aValue) {
  Bind();
  glTexParameteri(GL_TEXTURE_2D, aParam, aValue);
  Unbind();
}

/******************************************************************************/
void Texture::SetParameter(GLenum aParam, GLfloat aValue) {
  Bind();
  glTexParameterf(GL_TEXTURE_2D, aParam, aValue);
  Unbind();
}

/******************************************************************************/
void Texture::GenerateMipmap() {
  Bind();
  glGenerateMipmap(GL_TEXTURE_2D);
  Unbind();
}
} // namespace KumaGL
