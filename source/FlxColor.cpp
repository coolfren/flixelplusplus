#include "flixel++/FlxColor.hpp"

Flx::Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : r(red), g(green), b(blue), a(alpha)
{}

Flx::Color Flx::Color::fromHex(int color)
{
    return Color
    {
        static_cast<uint8_t>((color >> 24) & 0xFF), 
        static_cast<uint8_t>((color >> 16) & 0xFF), 
        static_cast<uint8_t>((color >> 8) & 0xFF), 
        static_cast<uint8_t>((color) & 0xFF)
    };
}