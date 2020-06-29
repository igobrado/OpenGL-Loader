#ifndef OPENGL_PBR_IAPPLICATION_HXX
#define OPENGL_PBR_IAPPLICATION_HXX

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class IApplication
{
public:
    virtual ~IApplication() = default;
    virtual int run() = 0;

protected:
    virtual void update(glm::mat4& projectionMatrix) = 0;
};
#endif //OPENGL_PBR_IAPPLICATION_HXX
