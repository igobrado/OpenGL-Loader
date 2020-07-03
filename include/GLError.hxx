#ifndef OPENGL_PBR_GLERROR_HXX
#define OPENGL_PBR_GLERROR_HXX

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <sstream>

#include "common/Logging.hxx"

static void GLClearError()
{
    // clang-format off
    while (glGetError() != GL_NO_ERROR); //
    // clang-format on
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::stringstream ss;
        ss << "[OPENGL ERROR]"
           << "(" << error << "): " << function << " " << file << " " << line << std::endl;

        OGL_CORE_ERROR(ss.str().c_str());
        return false;
    }
    return true;
}

#define GlCall(x)   \
    GLClearError(); \
    x;              \
    assert(GLLogCall(#x, __FILE__, __LINE__))

#endif  //! OPENGL_PBR_GLERROR_HXX