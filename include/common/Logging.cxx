#include "Logging.hxx"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace core {

std::shared_ptr<spdlog::logger> Logging::sCoreLogger;

void Logging::init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    sCoreLogger = spdlog::stdout_color_mt("OpenGL-PBR");
    sCoreLogger->set_level(spdlog::level::trace);
}

} // namespace core