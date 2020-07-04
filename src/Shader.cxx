#include "Shader.hxx"

#include <csignal>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

#include "GLError.hxx"
#include "UniformNames.hxx"
#include "common/Logging.hxx"
#include "property/PointLight.hxx"

Shader::Shader(const char* vertexShader, const char* fragmentShader)  //
    : mShaderID{ 0 }
    , mPointLightsContexts{}
{
    createShaderFromFile(vertexShader, fragmentShader);
}

Shader::~Shader()
{
    clearShader();
}

void Shader::createShaderFromString(const char* vertexShader, const char* fragmentShader)
{
    compileShader(vertexShader, fragmentShader);
}

void Shader::createShaderFromFile(const char* vertexShader, const char* fragmentShader)
{
    std::string vertexString   = readFile(vertexShader);
    std::string fragmentString = readFile(fragmentShader);

    compileShader(vertexString.c_str(), fragmentString.c_str());
    OGL_CORE_INFO("Compiling shaders went successfully!");
}

void Shader::updateGlUniformMat4(const char* uniformName, std::uint32_t count, bool transpose, glm::mat4 value)
{
    auto uniformLocation = getUniformLocation(uniformName);
    GlCall(glUniformMatrix4fv(uniformLocation, count, transpose, glm::value_ptr(value)));
}

void Shader::updateGlUniform3f(const char* uniformName, glm::vec3 values)
{
    auto uniformLocation = getUniformLocation(uniformName);
    GlCall(glUniform3f(uniformLocation, values.x, values.y, values.z));
}

void Shader::updateGlUniform1f(const char* uniformName, float& value)
{
    auto uniformLocation = getUniformLocation(uniformName);
    GlCall(glUniform1f(uniformLocation, value));
}

void Shader::updateGlUniform1i(const char* uniformName, std::uint32_t& value)
{
    auto uniformLocation = getUniformLocation(uniformName);
    glUniform1i(uniformLocation, value);
}

void Shader::updateGlUniform3f(std::uint32_t location, glm::vec3& value)
{
    GlCall(glUniform3f(location, value.x, value.y, value.z));
}

void Shader::updateGlUniform1f(std::uint32_t location, float& value)
{
    GlCall(glUniform1f(location, value));
}

void Shader::updateGlUniformMat4(std::uint32_t location, std::uint32_t count, bool transpose, glm::mat4& value)
{
    GlCall(glUniformMatrix4fv(location, count, transpose, glm::value_ptr(value)));
}

void Shader::updateGlUniform1i(std::uint32_t location, std::uint32_t& value)
{
    glUniform1i(location, value);
}

PointLightContext& Shader::getPointLightContext(int index)
{
    return mPointLightsContexts[index];
}

void Shader::useShader()
{
    if (mShaderID)
    {
        GlCall(glUseProgram(mShaderID));
    }
    else
    {
        OGL_CORE_ERROR("Binding shader and shader is not set!!!");
    }
}

void Shader::clearShader()
{
    if (!mShaderID)
    {
        GlCall(glDeleteProgram(mShaderID));
        mShaderID = 0;
    }
}

void Shader::compileShader(const char* vertexShader, const char* fragmentShader)
{
    mShaderID = glCreateProgram();
    if (!mShaderID)
    {
        OGL_CORE_ERROR("Error creating shader!\n");
        return;
    }
    addShader(mShaderID, vertexShader, ShaderType::VERTEX);
    addShader(mShaderID, fragmentShader, ShaderType::FRAGMENT);

    GLint  result{ 0 };
    GLchar eLog[1024]{ 0 };

    GlCall(glLinkProgram(mShaderID));
    GlCall(glGetProgramiv(mShaderID, GL_LINK_STATUS, &result));
    if (!result)
    {
        glGetProgramInfoLog(mShaderID, sizeof(eLog), nullptr, eLog);
        std::string out{ "Error linking program: " + std::string{ eLog } + "\n" };
        OGL_CORE_ERROR(out.c_str());
        return;
    }

    glValidateProgram(mShaderID);
    glGetProgramiv(mShaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(mShaderID, sizeof(eLog), nullptr, eLog);
        std::string out{ "Error validating program: " + std::string{ eLog } + "\n" };
        OGL_CORE_ERROR(out.c_str());
        return;
    }
    // Just to register the uniform
    (void)getUniformLocation(uPointLightCount);

    for (int i = 0; i < MAX_POINT_LIGHTS; ++i)
    {
        PointLightContext pointContext;
        char              locBuff[100] = { '\0' };

        std::snprintf(locBuff, sizeof(locBuff), "%s[%d]%s", uPointLights, i, uBaseCol);
        pointContext.uniformColor = getUniformLocation(locBuff);

        std::snprintf(locBuff, sizeof(locBuff), "%s[%d]%s", uPointLights, i, uBaseAIntensity);
        pointContext.uniformAmbientIntensity = getUniformLocation(locBuff);

        std::snprintf(locBuff, sizeof(locBuff), "%s[%d]%s", uPointLights, i, uBaseDIntensity);
        pointContext.uniformDiffuseIntensity = getUniformLocation(locBuff);

        std::snprintf(locBuff, sizeof(locBuff), "%s[%d]%s", uPointLights, i, uPointLightPos);
        pointContext.uniformPosition = getUniformLocation(locBuff);

        std::snprintf(locBuff, sizeof(locBuff), "%s[%d]%s", uPointLights, i, uPointLightCon);
        pointContext.uniformConstant = getUniformLocation(locBuff);

        std::snprintf(locBuff, sizeof(locBuff), "%s[%d]%s", uPointLights, i, uPointLightLin);
        pointContext.uniformLinear = getUniformLocation(locBuff);

        std::snprintf(locBuff, sizeof(locBuff), "%s[%d]%s", uPointLights, i, uPointLightExp);
        pointContext.uniformExponent = getUniformLocation(locBuff);

        mPointLightsContexts.push_back(pointContext);
    }
}

void Shader::addShader(std::uint32_t theProgram, const char* shaderCode, ShaderType shaderType)
{
    std::uint32_t theShader = glCreateShader(static_cast<GLenum>(shaderType));
    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = std::strlen(shaderCode);
    GlCall(glShaderSource(theShader, 1, theCode, codeLength));
    GlCall(glCompileShader(theShader));

    GLint  result{ 0 };
    GLchar eLog[1024]{ 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(mShaderID, sizeof(eLog), nullptr, eLog);
        OGL_CORE_ERROR(
                "Error compiling %s shader: %s\n",
                shaderType == ShaderType::VERTEX ? "vertex" : "fragment",
                eLog);
        return;
    }
    glAttachShader(theProgram, theShader);
}

std::string Shader::readFile(const char* fileLocation)
{
    std::string   content{};
    std::ifstream file{ fileLocation, std::ios::in };
    if (file.is_open())
    {
        std::string line{ "" };
        while (!file.eof())
        {
            std::getline(file, line);
            line.append("\n");
            content.append(line);
        }
    }
    else
    {
        OGL_CORE_ERROR("Failed to open file %s", fileLocation);
    }
    return content;
}

std::uint32_t Shader::getUniformLocation(const char* uniformName) const
{
    if (mUniformCache.find(uniformName) != mUniformCache.end())
        return mUniformCache[uniformName];

    auto location = glGetUniformLocation(mShaderID, uniformName);
    if (location < 0)
        std::raise(SIGINT);

    mUniformCache[uniformName] = location;
    return location;
}
