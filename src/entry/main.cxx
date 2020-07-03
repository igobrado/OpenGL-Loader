#define STB_IMAGE_IMPLEMENTATION

#include "OpenGLPBR.hxx"
#include "common/Logging.hxx"

int main(int argc, char** argv)
{
    core::Logging::init();
    std::unique_ptr<IApplication> app = std::make_unique<OpenGLPBR>(1366, 768);
    return app->run();
}