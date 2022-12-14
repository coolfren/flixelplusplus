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
        static Flx::Graphic* loadFromPath(const char* path);
    };
}

#endif