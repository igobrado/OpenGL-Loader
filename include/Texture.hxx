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

enum class TextureRgbType : int
{
    RGBA = GL_RGBA,
    RGB = GL_RGB,
};

class Texture
{
public:
    Texture(const char* fileLocation, TextureType textureType = TextureType::TEXTURE_2D, TextureRgbType rgba = TextureRgbType::RGB);
    ~Texture();

    TextureType getTextureType();

    bool loadTexture();
    bool loadAlfaTexture();
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
        TextureRgbType rgbaType;
    } mTextureContext;
};

#endif  //! OPENGL_PBR_TEXTURE_HXX