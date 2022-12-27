#include "flixel++/FlxKeyboard.hpp"

Flx::Keyboard::Keyboard()
    : keys(new bool[255])
{
}

bool Flx::Keyboard::pressed(const char key)
{
    return keys[key];
}

bool Flx::Keyboard::justPressed(const char key){
    bool pressed = keys[key];
    keys[key] = false;
    return pressed;
}