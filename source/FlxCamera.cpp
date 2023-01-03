#include "flixel++/FlxCamera.hpp"

Flx::Camera::Camera()
{
    canvas = new Flx::Sprite(0,0);
}

Flx::Camera::~Camera()
{
    delete canvas;
}

void Flx::Camera::drawSprites()
{

}

void Flx::Camera::ClearCanvas()
{

}
