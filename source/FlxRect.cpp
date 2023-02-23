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