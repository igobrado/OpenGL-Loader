#ifndef OPENGL_PBR_IAPPLICATION_HXX
#define OPENGL_PBR_IAPPLICATION_HXX

class IApplication
{
public:
    virtual ~IApplication() = default;
    virtual int run() = 0;

protected:
    virtual int update() = 0;
};
#endif //OPENGL_PBR_IAPPLICATION_HXX
