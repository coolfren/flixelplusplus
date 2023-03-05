#ifndef FLXSPRITE_HPP
#define FLXSPRITE_HPP
#include "flixel++/FlxObject.hpp"
#include "flixel++/FlxGraphic.hpp"
#include "flixel++/FlxRect.hpp"
#include "flixel++/FlxPoint.hpp"
#include "flixel++/FlxAnimation.hpp"
#include "flixel++/FlxColor.hpp"
#include "flixel++/FlxShader.hpp"
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
        
        Flx::Color color;

        Flx::Shader shader;

        Sprite(float x, float y);
        Sprite(const char* path);
        Sprite();
        ~Sprite();

        Flx::Sprite* loadGraphic(const char* path);
        Flx::Sprite* loadGraphic(const void* data, const size_t size);
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