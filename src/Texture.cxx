#include "Texture.hxx"

#include "common/Logging.hxx"

Texture::Texture(const char* fileLoc)
    : mTextureID{ 0U }
    , mWidth{ 0U }
    , mHeight{ 0U }
    , mBitDepth{ 0U }
    , mFileLocation{ fileLoc }
{
}

Texture::~Texture()
{
    clearTexture();
}

void Texture::loadTexture()
{
    unsigned char* texData = stbi_load(mFileLocation.c_str(), &mWidth, &mHeight, &mBitDepth, 0);

    if (!texData)
    {
        std::string log{ "Failed to load texture " + mFileLocation };
        OGL_CORE_ERROR(log.c_str());
    }
    else
    {
        glGenTextures(1, &mTextureID);
        glBindTexture(GL_TEXTURE_2D, mTextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(texData);
        OGL_CORE_INFO("Successively loaded texture\n.");
    }
}

void Texture::useTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Texture::clearTexture()
{
    glDeleteTextures(1, &mTextureID);
    mTextureID = 0;
    mWidth     = 0;
    mHeight    = 0;
    mBitDepth  = 0;
    mFileLocation.clear();
}