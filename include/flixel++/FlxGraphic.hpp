#ifndef FLXGRAPHIC_HPP
#define FLXGRAPHIC_HPP
#include "flixel++/Common.hpp"
namespace Flx
{

    class Graphic
    {
        private:
        Graphic(int width, int height, Bitmap* tex);
        public:
        ~Graphic();
        int width, height;
        Bitmap* bitmap;
        uint32_t getPixel32(int x, int y);
        static Flx::Graphic* loadFromPath(const char* path);
        static Flx::Graphic* loadFromSurface(SDL_Surface* surface);
        static Flx::Graphic* loadFromRAWPath(SDL_RWops* raw);
        friend class Sprite;
    };
}

#endif