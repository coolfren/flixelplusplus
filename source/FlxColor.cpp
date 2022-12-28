#include "flixel++/FlxColor.hpp"

Flx::Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : SDL_Color{red, green, blue, alpha}
{}

Flx::Color Flx::Color::fromHex(int color)
{
    return Color
    {
        ((color >> 24) & 0xFF), 
        ((color >> 16) & 0xFF), 
        ((color >> 8) & 0xFF), 
        ((color) & 0xFF)
    };
}