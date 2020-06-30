#ifndef OPENGL_PBR_CAMERA_H
#define OPENGL_PBR_CAMERA_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
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

    void keyControl(const Keyboard& keyboard, float deltaTime);
    void mouseControl(Mouse& mouse);

    glm::mat4 claculateViewMatrix();

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
    } mCameraContext;

    float mMovementSpeed;
    float mTurnSpeed;
};

#endif  // OPENGL_PBR_CAMERA_H
