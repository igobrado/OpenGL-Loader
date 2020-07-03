#ifndef OPENGL_PBR_CAMERA_H
#define OPENGL_PBR_CAMERA_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Keyboard.hxx"
#include "Mouse.hxx"

class Camera
{
public:
    Camera(glm::vec3 startPosition,
           glm::vec3 startUp,
           float     startYaw,
           float     startPitch,
           float     startMovementSpeed,
           float     startTurnSpeed);

    void resetCameraContext();

    glm::vec3 getCameraPosition();
    void      keyControl(const Keyboard& keyboard, float deltaTime);
    void      mouseControl(Mouse& mouse);
    glm::mat4 claculateViewMatrix();

    std::function<void(float, float, bool)> getOnMouseMoveCallbackFN();

protected:
    void update();

private:
    struct CameraContext
    {
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        float yaw;
        float pitch;

        const CameraContext& operator=(const CameraContext& defaultCameraContext)
        {
            position = defaultCameraContext.position;
            front    = defaultCameraContext.front;
            up       = defaultCameraContext.up;
            right    = defaultCameraContext.right;
            worldUp  = defaultCameraContext.worldUp;
            yaw      = defaultCameraContext.yaw;
            pitch    = defaultCameraContext.pitch;

            return *this;
        }
    } mCameraContext, mDefaultCameraContext;

    float mMovementSpeed;
    float mTurnSpeed;

    bool mCaptureMouseEvents;
};

#endif  // OPENGL_PBR_CAMERA_H
