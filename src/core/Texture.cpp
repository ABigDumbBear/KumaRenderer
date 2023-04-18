#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <glad/glad.h>

namespace Kuma3D {

/******************************************************************************/
Texture::Texture()
{
  // Generate an OpenGL texture.
  glGenTextures(1, &mID);
}

/******************************************************************************/
Texture::~Texture()
{
  glDeleteTextures(1, &mID);
}

/******************************************************************************/
void Texture::LoadFromFile(const std::string& aFile,
                           TextureStorageFormat aFormat,
                           TextureWrapOption aWrapOption,
                           TextureFilterOption aFilterOption)
{
  stbi_set_flip_vertically_on_load(true);

  int width, height, channels;
  auto data = stbi_load(aFile.c_str(),
                        &width,
                        &height,
                        &channels,
                        0);
  LoadFromData(data,
               width,
               height,
               aFormat,
               aWrapOption,
               aFilterOption);

  stbi_image_free(data);
}

/******************************************************************************/
void Texture::LoadFromData(unsigned char* aData,
                           unsigned int aWidth,
                           unsigned int aHeight,
                           TextureStorageFormat aFormat,
                           TextureWrapOption aWrapOption,
                           TextureFilterOption aFilterOption)
{
  // Store the texture's width and height.
  mWidth = aWidth;
  mHeight = aHeight;

  GLint loadFormat, wrapOption, filterOption;
  switch(aFormat)
  {
    case TextureStorageFormat::eR: { loadFormat = GL_RED; break; }
    case TextureStorageFormat::eRGB: { loadFormat = GL_RGB; break; }
    case TextureStorageFormat::eRGBA: { loadFormat = GL_RGBA; break; }
  }

  switch(aWrapOption)
  {
    case TextureWrapOption::eREPEAT: { wrapOption = GL_REPEAT; break; }
    case TextureWrapOption::eMIRRORED_REPEAT: { wrapOption = GL_MIRRORED_REPEAT; break; }
    case TextureWrapOption::eCLAMP_TO_EDGE: { wrapOption = GL_CLAMP_TO_EDGE; break; }
    case TextureWrapOption::eCLAMP_TO_BORDER: { wrapOption = GL_CLAMP_TO_BORDER; break; }
  }

  switch(aFilterOption)
  {
    case TextureFilterOption::eNEAREST: { filterOption = GL_NEAREST; break; }
    case TextureFilterOption::eLINEAR: { filterOption = GL_LINEAR; break; }
  }

  // Set default texture wrapping and filtering options.
  glBindTexture(GL_TEXTURE_2D, mID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapOption);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapOption);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterOption);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterOption);

  // Copy the image data into the currently bound texture.
  glTexImage2D(GL_TEXTURE_2D,
               0,
               loadFormat,
               aWidth,
               aHeight,
               0,
               loadFormat,
               GL_UNSIGNED_BYTE,
               aData);

  // Create a mipmap for this texture; used on small/far away objects.
  glGenerateMipmap(GL_TEXTURE_2D);
}

/*****************************************************************************/
void Texture::AddSubImageData(unsigned char* aData,
                              unsigned int aXOffset,
                              unsigned int aYOffset,
                              unsigned int aWidth,
                              unsigned int aHeight,
                              TextureStorageFormat aFormat)
{
  // Bind texture for use.
  glBindTexture(GL_TEXTURE_2D, mID);

  GLint loadFormat;
  switch(aFormat)
  {
    case TextureStorageFormat::eR: { loadFormat = GL_RED; break; }
    case TextureStorageFormat::eRGB: { loadFormat = GL_RGB; break; }
    case TextureStorageFormat::eRGBA: { loadFormat = GL_RGBA; break; }
  }

  // Add the image data to the existing texture.
  glTexSubImage2D(GL_TEXTURE_2D,
                  0,
                  aXOffset,
                  aYOffset,
                  aWidth,
                  aHeight,
                  loadFormat,
                  GL_UNSIGNED_BYTE,
                  aData);

  // Recreate the texture mipmap with the new data.
  glGenerateMipmap(GL_TEXTURE_2D);
}

} // namespace Kuma3D
