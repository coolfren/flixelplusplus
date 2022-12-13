#ifndef FLXSPRITE_HPP
#define FLXSPRITE_HPP
#include "flixel++/FlxObject.hpp"
#include "flixel++/FlxGraphic.hpp"
#include "flixel++/FlxRect.hpp"

namespace Flx
{
    class Sprite : public Flx::Object
    {
        public:
        Flx::Graphic* graphic;
        Flx::Rect clipRect;
        Flx::Rect hitbox;
        Sprite(float x, float y);
        ~Sprite();
        Flx::Sprite* loadGraphic(const char* path);
        void setGraphicSize(float width, float height);
        void screenCenter();
        void updateHitbox();
        void update();
        void draw();
    };
}

#endif