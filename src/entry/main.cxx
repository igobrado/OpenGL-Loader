#include "OpenGLPBR.hxx"
#include "common/Logging.hxx"
int main(int argc, char** argv)
{
    core::Logging::init();
    std::unique_ptr<IApplication> app = std::make_unique<OpenGLPBR>(800, 600);
    return app->run();
}