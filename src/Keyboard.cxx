#include "Keyboard.hxx"

#include "Window.hxx"
#include "common/Logging.hxx"

Keyboard::Keyboard()  //
    : mKeys{ false }
{
}

std::array<bool, 1024>& Keyboard::getKeys()
{
    return mKeys;
}

bool Keyboard::isKeyPressed(int code) const
{
    return mKeys[code];
}
