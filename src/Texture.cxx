#include "Texture.hxx"

#include "common/Logging.hxx"

Texture::Texture(const char* fileLoc, TextureType textureType)
    : mTextureContext{ 0U, 0U, 0U, 0U, fileLoc, textureType }
{
}

Texture::~Texture()
{
    clearTexture();
}

TextureType Texture::getTextureType()
{
    return mTextureContext.textureType;
}

void Texture::loadTexture()
{
    unsigned char* texData = stbi_load(
            mTextureContext.fileLocation.c_str(),
            &mTextureContext.width,
            &mTextureContext.height,
            &mTextureContext.bitDepth,
            0);

    if (!texData)
    {
        std::string log{ "Failed to load texture " + mTextureContext.fileLocation };
        OGL_CORE_ERROR(log.c_str());
    }
    else
    {
        glGenTextures(1, &mTextureContext.textureID);
        glBindTexture(GL_TEXTURE_2D, mTextureContext.textureID);

        glTexParameteri((int) mTextureContext.textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri((int) mTextureContext.textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri((int) mTextureContext.textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri((int) mTextureContext.textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(
                (int) mTextureContext.textureType,
                0,
                GL_RGBA,
                mTextureContext.width,
                mTextureContext.height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                texData);
        glGenerateMipmap((int) mTextureContext.textureType);

        glBindTexture((int) mTextureContext.textureType, 0);
        stbi_image_free(texData);
        OGL_CORE_INFO("Successively loaded texture\n.");
    }
}

void Texture::useTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture((int) mTextureContext.textureType, mTextureContext.textureID);
}

void Texture::clearTexture()
{
    glDeleteTextures(1, &mTextureContext.textureID);
    mTextureContext.textureID = 0;
    mTextureContext.width     = 0;
    mTextureContext.height    = 0;
    mTextureContext.bitDepth  = 0;
    mTextureContext.fileLocation.clear();
}