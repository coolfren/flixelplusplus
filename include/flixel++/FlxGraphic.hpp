#ifndef FLXGRAPHIC_HPP
#define FLXGRAPHIC_HPP
#include "flixel++/Common.hpp"
namespace Flx
{

    class Graphic
    {
        public:
        Graphic(int width, int height, void* tex);
        ~Graphic();
        int width, height;
        void* bitmap;
        uint32_t getPixel32(int x, int y);
        friend class Sprite;
    };
}

#endif