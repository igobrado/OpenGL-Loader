#include "Camera.hxx"

Camera::Camera(
        glm::vec3 startPosition,
        glm::vec3 startUp,
        float     startYaw,
        float     startPitch,
        float     startMovementSpeed,
        float     startTurnSpeed)  //
    : mCameraContext{ startPosition,
                      glm::vec3(0.0f, -1.0f, 0.0f),
                      glm::vec3{ 0.0f, 0.0f, 0.0f },
                      glm::vec3{ 0.0f, 0.0f, 0.0f },
                      startUp,
                      startYaw,
                      startPitch }
    , mMovementSpeed{ startMovementSpeed }
    , mTurnSpeed{ startTurnSpeed }
{
    update();
}

void Camera::update()
{
    mCameraContext.front.x = std::cos(glm::radians(mCameraContext.yaw)) * std::cos(glm::radians(mCameraContext.pitch));
    mCameraContext.front.y = std::sin(glm::radians(mCameraContext.pitch));
    mCameraContext.front.z = std::sin(glm::radians(mCameraContext.yaw)) * std::cos(glm::radians(mCameraContext.pitch));
    mCameraContext.front   = glm::normalize(mCameraContext.front);

    mCameraContext.right = glm::normalize(glm::cross(mCameraContext.front, mCameraContext.worldUp));
    mCameraContext.up    = glm::normalize(glm::cross(mCameraContext.right, mCameraContext.front));
}

void Camera::keyControl(const Keyboard& keyboard, float deltaTime)
{
    auto velocity = deltaTime * mMovementSpeed;
    if (keyboard.isKeyPressed(GLFW_KEY_W))
    {
        mCameraContext.position += mCameraContext.front * velocity;
    }
    else if (keyboard.isKeyPressed(GLFW_KEY_S))
    {
        mCameraContext.position -= mCameraContext.front * velocity;
    }
    else if (keyboard.isKeyPressed(GLFW_KEY_A))
    {
        mCameraContext.position -= mCameraContext.right * velocity;
    }
    else if (keyboard.isKeyPressed(GLFW_KEY_D))
    {
        mCameraContext.position += mCameraContext.right * velocity;
    }
}

void Camera::mouseControl(Mouse& mouse)
{
    if (mouse.captureEvents())
    {
        float xChange = mouse.getXChange();
        float yChange = mouse.getYChange();

        xChange *= mTurnSpeed;
        yChange *= mTurnSpeed;

        mCameraContext.yaw += xChange;
        mCameraContext.pitch += yChange;

        mCameraContext.pitch = mCameraContext.pitch > 89.9f ? 89.0f : mCameraContext.pitch;
        mCameraContext.pitch = mCameraContext.pitch < -89.9f ? -89.0f : mCameraContext.pitch;

        update();
    }
}

glm::mat4 Camera::claculateViewMatrix()
{
    return glm::lookAt(mCameraContext.position, mCameraContext.position + mCameraContext.front, mCameraContext.up);
}