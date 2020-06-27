#ifndef OPENGL_PBR_LOGGING_H
#define OPENGL_PBR_LOGGING_H

#include <memory>

#include "spdlog/spdlog.h"

namespace core {

class Logging
{
public:
    static void init();
    inline static std::shared_ptr<spdlog::logger>& getCoreLogger()
    {
        return sCoreLogger;
    };

private:
    static std::shared_ptr<spdlog::logger> sCoreLogger;
};

} // namespace core

#define OGL_CORE_ERROR(...) ::core::Logging::getCoreLogger()->error(__VA_ARGS__)
#define OGL_CORE_WARN(...) ::core::Logging::getCoreLogger()->warn(__VA_ARGS__)
#define OGL_CORE_FATAL(...) ::core::Logging::getCoreLogger()->fatal(__VA_ARGS__)
#define OGL_CORE_INFO(...) ::core::Logging::getCoreLogger()->info(__VA_ARGS__)

#endif // OPENGL_PBR_LOGGING_H
