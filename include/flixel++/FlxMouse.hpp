#ifndef FLXMOUSE_HPP
#define FLXMOUSE_HPP

#include "flixel++/Common.hpp"
#include "flixel++/FlxBasic.hpp"
#include "flixel++/FlxAssets.hpp"
#include "flixel++/FlxRect.hpp"
#include "flixel++/FlxPoint.hpp"

namespace Flx {
    class Mouse
    {
        public:
        Mouse();
        ~Mouse();

        void draw();
        void update();
        void loadGraphic(const char* path);

        Flx::Rect clipRect;
        Bitmap* cursor;
        Flx::Point pos;

        bool enable;

        float x,y;

        private:
        void setGraphic();
    };
}

#endif