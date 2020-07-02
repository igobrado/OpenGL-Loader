#include "Shader.hxx"

#include <sstream>

#include "UniformNames.hxx"
#include "common/Logging.hxx"

Shader::Shader()  //
    : mShaderID{ 0 }
    , mUniformProjection{ 0 }
    , mUniformModel{ 0 }
{
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

std::uint32_t Shader::getProjectionMatrixLocation() const
{
    return mUniformProjection;
}

std::uint32_t Shader::getModelMatrixLocation() const
{
    return mUniformModel;
}

std::uint32_t Shader::getViewLocation() const
{
    return mUniformView;
}

std::uint32_t Shader::getUniformAmbientIntensityLocation() const
{
    return mUniformAmbientIntensity;
}

std::uint32_t Shader::getUniformColorLocation() const
{
    return mUniformColor;
}

std::uint32_t Shader::getUniformDiffuseIntensityLocation() const
{
    return mUniformDiffuseIntensity;
}

std::uint32_t Shader::getUniformDirectionLocation() const
{
    return mUniformDirection;
}

void Shader::useShader()
{
    if (mShaderID)
    {
        glUseProgram(mShaderID);
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
        glDeleteProgram(mShaderID);
        mShaderID = 0;
    }
    mUniformModel      = 0;
    mUniformProjection = 0;
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

    glLinkProgram(mShaderID);
    glGetProgramiv(mShaderID, GL_LINK_STATUS, &result);
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

    mUniformModel            = glGetUniformLocation(mShaderID, uModel);
    mUniformProjection       = glGetUniformLocation(mShaderID, uProjection);
    mUniformView             = glGetUniformLocation(mShaderID, uView);
    mUniformAmbientIntensity = glGetUniformLocation(mShaderID, uAmbientIntensity);
    mUniformColor            = glGetUniformLocation(mShaderID, uColor);
    mUniformDiffuseIntensity = glGetUniformLocation(mShaderID, uDiffuseIntensity);
    mUniformDirection        = glGetUniformLocation(mShaderID, uDirection);
}

void Shader::addShader(std::uint32_t theProgram, const char* shaderCode, ShaderType shaderType)
{
    std::uint32_t theShader = glCreateShader(static_cast<GLenum>(shaderType));
    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = std::strlen(shaderCode);
    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

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
