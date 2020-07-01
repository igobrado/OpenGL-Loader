#ifndef OPENGL_PBR_TEXTURE_HXX
#define OPENGL_PBR_TEXTURE_HXX

#include <GL/glew.h>

#include <string>

#include "stb_image.h"

class Texture
{
public:
    Texture(const char* fileLocation);
    ~Texture();

    void loadTexture();
    void useTexture();
    void clearTexture();

private:
    std::uint32_t mTextureID;
    std::int32_t mWidth;
    std::int32_t mHeight;
    std::int32_t mBitDepth;
    std::string   mFileLocation;
};
#endif  //! OPENGL_PBR_TEXTURE_HXX