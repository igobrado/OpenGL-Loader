#include "OpenGLPBR.hxx"

int main(int argc, char** argv)
{
    std::unique_ptr<IApplication> app = std::make_unique<OpenGLPBR>(800, 600);
    return app->run();
}