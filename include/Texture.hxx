#ifndef OPENGL_PBR_TEXTURE_HXX
#define OPENGL_PBR_TEXTURE_HXX

#include <GL/glew.h>

#include <string>

#include "stb_image.h"

enum class TextureType : int
{
    TEXTURE_2D = GL_TEXTURE_2D,
    TEXTURE_3D = GL_TEXTURE_3D,
};

class Texture
{
public:
    Texture(const char* fileLocation, TextureType textureType = TextureType::TEXTURE_2D);
    ~Texture();

    TextureType getTextureType();

    void loadTexture();
    void useTexture();
    void clearTexture();

private:
    struct TextureContext
    {
        std::uint32_t textureID;
        std::int32_t  width;
        std::int32_t  height;
        std::int32_t  bitDepth;
        std::string   fileLocation;

        TextureType textureType;
    } mTextureContext;
};

#endif  //! OPENGL_PBR_TEXTURE_HXX