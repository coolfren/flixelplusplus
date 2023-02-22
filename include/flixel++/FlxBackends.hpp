#ifndef FLXBACKENDS_HPP
#define FLXBACKENDS_HPP
#include "flixel++/FlxSprite.hpp"
#include "flixel++/FlxGraphic.hpp"

namespace Flx::Backends
{
    class Backend
    {
        public:
        Backend();
        virtual ~Backend();
        virtual Flx::Graphic* requestTexture(const char* path);
        virtual Flx::Graphic* requestTexture(const void* data, const size_t size);
        virtual bool deleteTexture(void* tex);
        virtual void runEvents();
        virtual void update();
        virtual void render(Flx::Sprite* spr);
        virtual uint32_t getTicks();
    };

    class SDL : public Backend
    {
        private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        public:
        SDL();
        ~SDL();
        Flx::Graphic* requestTexture(const char* path);
        Flx::Graphic* requestTexture(const void* data, const size_t size);
        Flx::Graphic* requestTexture(SDL_Surface* surface);
        bool deleteTexture(void* tex);
        void runEvents();
        void update();
        void render(Flx::Sprite* spr);
        uint32_t getTicks();
    };

    class OpenGL : public Backend
    {};
}

#endif