#ifndef OPENGL_PBR_SHADER_HXX
#define OPENGL_PBR_SHADER_HXX

#include <GL/glew.h>

#include <fstream>
#include <string>

class Shader
{
    enum class ShaderType : GLenum
    {
        FRAGMENT = GL_FRAGMENT_SHADER,
        VERTEX   = GL_VERTEX_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER
    };

public:
    Shader();
    ~Shader();

    void createShaderFromString(const char* vertexShader, const char* fragmentShader);

    std::uint32_t getProjectionMatrixLocation() const;
    std::uint32_t getModelMatrixLocation() const;

    std::uint32_t getUniformLocation(const char* uniformName);

    void useShader();
    void clearShader();

protected:
    void compileShader(const char* vertexShader, const char* fragmentShader);
    void addShader(std::uint32_t theProgram, const char* shaderCode, ShaderType shaderType);

private:
    std::uint32_t mShaderID;
    std::uint32_t mUniformProjection;
    std::uint32_t mUniformModel;
};

#endif  // OPENGL_PBR_SHADER_HXX
