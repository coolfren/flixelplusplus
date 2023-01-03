#ifndef FLXSPRITE_HPP
#define FLXSPRITE_HPP
#include "flixel++/FlxObject.hpp"
#include "flixel++/FlxGraphic.hpp"
#include "flixel++/FlxRect.hpp"
#include "flixel++/FlxPoint.hpp"
#include "flixel++/FlxAnimation.hpp"

namespace Flx
{
    class Sprite : public Flx::Object
    {
    public:
        int alpha;
        int angle;
        bool visible;

        Flx::Graphic* graphic;
        Flx::Rect clipRect;
        Flx::Rect hitbox;
        Flx::AnimationController* animation;
        
        Sprite(float x, float y);
        ~Sprite();

        Flx::Sprite* loadGraphic(const char* path);
        Flx::Sprite* loadRAWGraphic(const void* data, const size_t size);
        Flx::Sprite* makeGraphic(float width, float height, int color);

        bool collides(Flx::Sprite* sprite);
        void setGraphicSize(float width, float height);
        void screenCenter();
        void updatePosition();
        void updateHitbox();
        void update();
        void draw();
         
        Flx::Point offset;
        Flx::Point scale;
        Flx::Point origin;
    };
}

#endif