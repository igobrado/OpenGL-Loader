#include "Camera.hxx"

Camera::Camera(
        glm::vec3 startPosition,
        glm::vec3 startUp,
        float     startYaw,
        float     startPitch,
        float     startMovementSpeed,
        float     startTurnSpeed)  //
    : mCameraContext{ startPosition,
                      glm::vec3(0.0f, 0.0f, 1.0f),
                      glm::vec3{ 0.0f, 0.0f, -1.0f },
                      glm::vec3{ 0.0f, 0.0f, 0.0f },
                      startUp,
                      startYaw,
                      startPitch }
    , mDefaultCameraContext{ startPosition,
                             glm::vec3(0.0f, 0.0f, 1.0f),
                             glm::vec3{ 0.0f, 0.0f, 0.0f },
                             glm::vec3{ 0.0f, 0.0f, 0.0f },
                             startUp,
                             startYaw,
                             startPitch }
    , mMovementSpeed{ startMovementSpeed }
    , mTurnSpeed{ startTurnSpeed }
    , mCaptureMouseEvents{ false }
{
    update();
}

void Camera::resetCameraContext()
{
    mCameraContext = mDefaultCameraContext;
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

glm::vec3& Camera::getCameraPosition()
{
    return mCameraContext.position;
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

glm::mat4& Camera::claculateViewMatrix()
{
    mViewMatrix = glm::lookAt(
            mCameraContext.position,
            mCameraContext.position + mCameraContext.front,
            mCameraContext.up);
    return mViewMatrix;
}

std::function<void(float, float, bool)> Camera::getOnMouseMoveCallbackFN()
{
    return [this](float xChange, float yChange, bool callUpdate) {
        xChange *= mTurnSpeed;
        yChange *= mTurnSpeed;

        mCameraContext.yaw += xChange;
        mCameraContext.pitch += yChange;

        mCameraContext.pitch = mCameraContext.pitch > 89.9f ? 89.0f : mCameraContext.pitch;
        mCameraContext.pitch = mCameraContext.pitch < -89.9f ? -89.0f : mCameraContext.pitch;

        if (callUpdate)
        {
            update();
        }
    };
}

glm::vec3 Camera::getCameraDirection()
{
    return glm::normalize(mCameraContext.front);
}
