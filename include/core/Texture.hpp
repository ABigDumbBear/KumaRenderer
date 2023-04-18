#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

namespace Kuma3D {

enum class TextureStorageFormat
{
  eR,
  eRGB,
  eRGBA
};

enum class TextureWrapOption
{
  eREPEAT,
  eMIRRORED_REPEAT,
  eCLAMP_TO_EDGE,
  eCLAMP_TO_BORDER
};

enum class TextureFilterOption
{
  eNEAREST,
  eLINEAR
};

class Texture
{
  public:
    Texture();
    ~Texture();

    void LoadFromFile(const std::string& aFile,
                      TextureStorageFormat aFormat = TextureStorageFormat::eRGBA,
                      TextureWrapOption aWrapOption = TextureWrapOption::eREPEAT,
                      TextureFilterOption aFilterOption = TextureFilterOption::eNEAREST);
    void LoadFromData(unsigned char* aData,
                      unsigned int aWidth,
                      unsigned int aHeight,
                      TextureStorageFormat aFormat = TextureStorageFormat::eRGBA,
                      TextureWrapOption aWrapOption = TextureWrapOption::eREPEAT,
                      TextureFilterOption aFilterOption = TextureFilterOption::eLINEAR);
    void AddSubImageData(unsigned char* aData,
                         unsigned int aXOffset,
                         unsigned int aYOffset,
                         unsigned int aWidth,
                         unsigned int aHeight,
                         TextureStorageFormat aFormat = TextureStorageFormat::eRGBA);

    unsigned int GetWidth() const { return mWidth; }
    unsigned int GetHeight() const { return mHeight; }

    unsigned int GetID() const { return mID; }

  private:
    unsigned int mWidth { 0 };
    unsigned int mHeight { 0 };

    unsigned int mID { 0 };
};

} // namespace Kuma3D

#endif
