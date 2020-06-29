#include "Camera.hxx"

Camera::Camera(
        glm::vec3 startPosition,
        glm::vec3 startUp,
        float     startYaw,
        float     startPitch,
        float     startMovementSpeed,
        float     startTurnSpeed)  //
    : mPosition{ startPosition }
    , mFront{ 0.0f, 0.0f, -1.0f }
    , mUP{}
    , mRight{ 0.0f }
    , mWorldUp{ startUp }
    , mYaw{ startYaw }
    , mPitch{ startPitch }
    , mMovementSpeed{ startMovementSpeed }
    , mTurnSpeed{ startTurnSpeed }
{
    update();
}

void Camera::update()
{
    mFront.x = std::cos(glm::radians(mYaw)) * std::cos(glm::radians(mPitch));
    mFront.y = std::sin(glm::radians(mPitch));
    mFront.z = std::sin(glm::radians(mYaw)) * std::cos(glm::radians(mPitch));
    mFront   = glm::normalize(mFront);

    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUP    = glm::normalize(glm::cross(mRight, mFront));
}

void Camera::keyControl(const Keyboard& keyboard, float deltaTime)
{
    auto velocity = deltaTime * mMovementSpeed;
    if (keyboard.isKeyPressed(GLFW_KEY_W))
    {
        mPosition += mFront * velocity;
    }
    else if (keyboard.isKeyPressed(GLFW_KEY_S))
    {
        mPosition -= mFront * velocity;
    }
    else if (keyboard.isKeyPressed(GLFW_KEY_A))
    {
        mPosition -= mRight * velocity;
    }
    else if (keyboard.isKeyPressed(GLFW_KEY_D))
    {
        mPosition += mRight * velocity;
    }
}

void Camera::mouseControl(const Mouse& mouse)
{
    float xChange = mouse.mChangePoint.X;
    float yChange = mouse.mChangePoint.Y;

    xChange *= mTurnSpeed;
    yChange *= mTurnSpeed;

    mYaw += xChange;
    mPitch += yChange;

    if (mPitch > 89.0f)
    {
        mPitch = 89.0f;
    }

    if (mPitch < -89.0f )
    {
        mPitch = -89.0f;
    }

    update();
}

glm::mat4 Camera::claculateViewMatrix()
{
    return glm::lookAt(mPosition, mPosition + mFront, mUP);
}

