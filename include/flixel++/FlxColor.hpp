#ifndef FLXCOLOR_HPP
#define FLXCOLOR_HPP
#include "flixel++/Common.hpp"

namespace Flx
{
    /**
     * The color class. This class represents the channels Red, Green, Blue and Alpha.
    */
    struct Color
    {
        uint8_t r, g, b, a;
        Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
        static Color fromHex(int color);
    };
}

#endif