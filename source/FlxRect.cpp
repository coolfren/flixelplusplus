#include "flixel++/FlxRect.hpp"

Flx::Rect::Rect()
    : x(0), y(0), width(0), height(0)
{
}

Flx::Rect::Rect(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height)
{
}

Flx::Rect::~Rect()
{
    
}

const SDL_Rect Flx::Rect::toSDLRect()
{
    return SDL_Rect{
        (Sint16)x,(Sint16)y,(Uint16)width,(Uint16)height
    };
}

const SDL_FRect Flx::Rect::toSDLFRect()
{
    return SDL_FRect{
        x,y,width,height
    };
}