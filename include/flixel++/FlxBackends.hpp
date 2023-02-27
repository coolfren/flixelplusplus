#ifndef FLXBACKENDS_HPP
#define FLXBACKENDS_HPP
#include "flixel++/FlxSprite.hpp"
#include "flixel++/FlxGraphic.hpp"

#ifdef FLIXEL_SDL
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
#endif

#ifdef FLIXEL_OPENGL
struct SDL_Window;
#endif

namespace Flx::Backends
{
    class Backend
    {
        public:
        Backend();
        virtual ~Backend();
        virtual Flx::Graphic* requestTexture(const char* path);
        virtual Flx::Graphic* requestTexture(const void* data, const size_t size);
        virtual Flx::Graphic* requestText(const char* text);
        virtual Flx::Graphic* requestRectangle(float width, float height, int color);
        virtual Flx::Shader* compileShader(Flx::Shader* shader);
        virtual bool deleteTexture(void* tex);
        virtual void runEvents();
        virtual void update();
        virtual void render(Flx::Sprite* spr);
        virtual uint32_t getTicks();
        virtual void delay(uint32_t ms);
    };

#ifdef FLIXEL_SDL
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
        Flx::Graphic* requestText(const char* text);
        Flx::Graphic* requestRectangle(float width, float height, int color);
        Flx::Shader* compileShader(Flx::Shader* shader);
        bool deleteTexture(void* tex);
        void runEvents();
        void update();
        void render(Flx::Sprite* spr);
        inline uint32_t getTicks();
        inline void delay(uint32_t ms);
    };
#endif

#ifdef FLIXEL_OPENGL
    class OpenGL : public Backend
    {
        private:
        SDL_Window* window;
        public:
        OpenGL();
        ~OpenGL();
        Flx::Graphic* requestTexture(const char* path);
        Flx::Graphic* requestTexture(const void* data, const size_t size);
        Flx::Graphic* requestText(const char* text);
        Flx::Graphic* requestRectangle(float width, float height, int color);
        Flx::Shader* compileShader(Flx::Shader* shader);
        bool deleteTexture(void* tex);
        void runEvents();
        void update();
        void render(Flx::Sprite* spr);
        uint32_t getTicks();
        void delay(uint32_t ms);
    };
#endif
}

#endif