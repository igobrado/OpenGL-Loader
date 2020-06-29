#ifndef OPENGL_PBR_CAMERA_H
#define OPENGL_PBR_CAMERA_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <array>
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
    void mouseControl(const Mouse& mouse);

    glm::mat4 claculateViewMatrix();
protected:
    void update();

private:
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mUP;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;

    float mYaw;
    float mPitch;

    float mMovementSpeed;
    float mTurnSpeed;
};

#endif  // OPENGL_PBR_CAMERA_H
