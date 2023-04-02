#include "flixel++/FlxKeyboard.hpp"
#include <cstring>

Flx::Keyboard::Keyboard()
    : keys(new bool[255])
{
    memset(keys, false, 255);
}

bool Flx::Keyboard::pressed(const unsigned char key)
{
    return keys[key];
}

bool Flx::Keyboard::justPressed(const unsigned char key){
    bool pressed = keys[key];
    if(pressed)
        keys[key] = false;
    return pressed;
}