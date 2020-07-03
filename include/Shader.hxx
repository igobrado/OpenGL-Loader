#ifndef OPENGL_PBR_SHADER_HXX
#define OPENGL_PBR_SHADER_HXX

#include <GL/glew.h>

#include <fstream>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader
{
    enum class ShaderType : GLenum
    {
        FRAGMENT = GL_FRAGMENT_SHADER,
        VERTEX   = GL_VERTEX_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER
    };

public:
    Shader(const char* vertexShader, const char* fragmentShader);
    ~Shader();

    void createShaderFromString(const char* vertexShader, const char* fragmentShader);
    void createShaderFromFile(const char* vertexShader, const char* fragmentShader);

    void updateGlUniformMat4(const char* uniformName, std::uint32_t count, bool transpose, glm::mat4 value);
    void updateGlUniform3f(const char* uniformName, glm::vec3 values);
    void updateUniform1f(const char* uniformName, float& value);

    void useShader();
    void clearShader();

protected:
    void        compileShader(const char* vertexShader, const char* fragmentShader);
    void        addShader(std::uint32_t theProgram, const char* shaderCode, ShaderType shaderType);
    std::string readFile(const char* fileLocation);

    std::uint32_t getUniformLocation(const char* uniformName) const;

private:
    std::uint32_t mShaderID;

    mutable std::unordered_map<std::string, std::uint32_t> mUniformCache;
};

#endif  // OPENGL_PBR_SHADER_HXX
