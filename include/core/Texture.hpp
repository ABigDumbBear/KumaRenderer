#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <glad/glad.h>

namespace Kuma3D {

class Texture
{
  public:
    Texture();
    ~Texture();

    void LoadFromFile(const std::string& aFile, GLint aLoadFormat = GL_RGBA);

    int GetWidth() const { return mWidth; }
    int GetHeight() const { return mHeight; }

    GLuint GetID() const { return mID; }

  private:
    int mWidth { 0 };
    int mHeight { 0 };

    GLuint mID { 0 };
};

} // namespace Kuma3D

#endif
