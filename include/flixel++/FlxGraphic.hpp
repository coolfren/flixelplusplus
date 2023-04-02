#ifndef FLXGRAPHIC_HPP
#define FLXGRAPHIC_HPP
#include "flixel++/Common.hpp"
#include "flixel++/FlxColor.hpp"

namespace Flx
{
    /**
     * The graphic class is a container for bitmaps.
    */
    class Graphic
    {
        public:
        Graphic(int width, int height, void* tex);
        ~Graphic();
        int width, height;
        /**
         * The graphic data that is stored in RAM
        */
        void* bitmap;
        Flx::Color getPixel32(int x, int y);
        friend class Sprite;

        static int currentID;

        unsigned int id;
        const char* path;
        int channels;
    };
}

#endif