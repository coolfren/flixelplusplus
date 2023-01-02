#include "flixel++/FlxPoint.hpp"

Flx::Point::Point()
    : x(0), y(0)
{}

Flx::Point::Point(float x, float y)
    : x(x), y(y)
{}

Flx::Point::~Point(){}

void Flx::Point::add(float x, float y) {
	this->x += x;
	this->y += y;
}

void Flx::Point::set(float x, float y) {
	this->x = x;
	this->y = y;
}

void Flx::Point::subtract(float x, float y) {
	this->x -= x;
	this->y -= y;
}

#ifndef SDL_LEGACY

const SDL_Point Flx::Point::toSDLPoint()
{
    return SDL_Point{
        static_cast<int>(x),
		static_cast<int>(y)
    };
}

const SDL_FPoint Flx::Point::toSDLFPoint()
{
    return SDL_FPoint{
        x,y
    };
}
#endif