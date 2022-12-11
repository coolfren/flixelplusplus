#ifndef FLXSPRITE_HPP
#define FLXSPRITE_HPP
#include "flixel++/FlxObject.hpp"
#include "flixel++/FlxGraphic.hpp"

namespace Flx
{
    class Sprite : public Flx::Object
    {
        public:
        Flx::Graphic* graphic;
        Sprite(float x, float y);
        ~Sprite();
        Flx::Sprite* loadGraphic(const char* path);
        void update();
        void draw();
    };
}

#endif