#include "Shader.hxx"

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

std::uint32_t Shader::getProjectionMatrixLocation() const
{
    return mUniformProjection;
}

std::uint32_t Shader::getModelMatrixLocation() const
{
    return mUniformModel;
}

std::uint32_t Shader::getUniformLocation(const char* uniformName)
{
    return 0;
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
    mUniformModel = 0;
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

    GLint result{0};
    GLchar eLog[1024]{0};

    glLinkProgram(mShaderID);
    glGetProgramiv(mShaderID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(mShaderID, sizeof(eLog), nullptr, eLog);
        OGL_CORE_ERROR("Error linking program: %s\n", eLog);
        return;
    }

    glValidateProgram(mShaderID);
    glGetProgramiv(mShaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(mShaderID, sizeof(eLog), nullptr, eLog);
        OGL_CORE_ERROR("Error validating program: %s\n", eLog);
        return;
    }

    mUniformModel = glGetUniformLocation(mShaderID, "uModel");
    mUniformProjection = glGetUniformLocation(mShaderID, "uProjection");
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

    GLint result{0};
    GLchar eLog[1024]{0};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(mShaderID, sizeof(eLog), nullptr, eLog);
        OGL_CORE_ERROR("Error compiling %s shader: %s\n", shaderType == ShaderType::VERTEX ? "vertex" : "fragment", eLog);
        return;
    }
    glAttachShader(theProgram, theShader);
}
