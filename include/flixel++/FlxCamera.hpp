#ifndef FLXCAMERA_HPP
#define FLXCAMERA_HPP

#include "Common.hpp"
#include "flixel++/FlxSprite.hpp"

namespace Flx{
    class Camera{
        public:
        Camera();
        ~Camera();

        Flx::Sprite* canvas;

        void drawSprites();
        void ClearCanvas();
        
        float zoom;
        float globalX,globalY;
    };
}

#endif