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

#ifdef FLIXEL_X11
struct Display;
struct Window;
struct Visual;
struct GC;
struct XEvent;
#endif

namespace Flx::Backends
{
    class Backend
    {
    public:
        virtual ~Backend(){};
        virtual Flx::Graphic *requestTexture(const char *path) = 0;
        virtual Flx::Graphic *requestTexture(const void *data, const size_t size) = 0;
        virtual Flx::Graphic *requestText(const char *text) = 0;
        virtual Flx::Graphic *requestRectangle(float width, float height, int color) = 0;
        virtual Flx::Shader *compileShader(Flx::Shader *shader) = 0;
        virtual bool deleteTexture(void *tex) = 0;
        virtual void runEvents() = 0;
        virtual void update() = 0;
        virtual void render(Flx::Sprite *spr) = 0;
        virtual uint32_t getTicks() = 0;
        virtual void delay(uint32_t ms) = 0;
    };

#ifdef FLIXEL_SDL
    class SDL : public Backend
    {
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

    public:
        SDL();
        ~SDL();
        Flx::Graphic *requestTexture(const char *path);
        Flx::Graphic *requestTexture(const void *data, const size_t size);
        Flx::Graphic *requestTexture(SDL_Surface *surface);
        Flx::Graphic *requestText(const char *text);
        Flx::Graphic *requestRectangle(float width, float height, int color);
        Flx::Shader *compileShader(Flx::Shader *shader);
        bool deleteTexture(void *tex);
        void runEvents();
        void update();
        void render(Flx::Sprite *spr);
        inline uint32_t getTicks();
        inline void delay(uint32_t ms);
        
    };
#endif

#ifdef FLIXEL_OPENGL
    class OpenGL : public Backend
    {
    private:
        SDL_Window *window;

    public:
        OpenGL();
        ~OpenGL();
        Flx::Graphic *requestTexture(const char *path);
        Flx::Graphic *requestTexture(const void *data, const size_t size);
        Flx::Graphic *requestText(const char *text);
        Flx::Graphic *requestRectangle(float width, float height, int color);
        Flx::Shader *compileShader(Flx::Shader *shader);
        bool deleteTexture(void *tex);
        void runEvents();
        void update();
        void render(Flx::Sprite *spr);
        uint32_t getTicks();
        void delay(uint32_t ms);
    };
#endif

#ifdef FLIXEL_X11
    class X11 : public Backend
    {
    private:
        Window window;
        Display* display;
        XEvent event;
        GC gc;
        Visual* visual;
        int screen;
    public:
        X11();
        ~X11();
        Flx::Graphic *createGraphic(Flx::Graphic *graphic);
        Flx::Graphic *requestTexture(const char *path);
        Flx::Graphic *requestTexture(const void *data, const size_t size);
        Flx::Graphic *requestText(const char *text);
        Flx::Graphic *requestRectangle(float width, float height, int color);
        Flx::Shader *compileShader(Flx::Shader *shader);
        bool deleteTexture(void *tex);
        void runEvents();
        void update();
        void render(Flx::Sprite *spr);
        uint32_t getTicks();
        void delay(uint32_t ms);
    };
#endif

}

#endif