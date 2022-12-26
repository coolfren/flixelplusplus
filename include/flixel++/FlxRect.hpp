#ifndef FLXRECT_HPP
#define FLXRECT_HPP
#include "flixel++/Common.hpp"

namespace Flx
{
    struct Rect
    {

        Rect();
        Rect(float x, float y, float width, float height);
        ~Rect();

        float x, y;
        float width, height;

        const SDL_Rect toSDLRect();
        const SDL_FRect toSDLFRect();
    };
}
#endif