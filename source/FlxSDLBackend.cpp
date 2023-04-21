#include "flixel++/Common.hpp"
#include "flixel++/FlxBackends.hpp"
#include "flixel++/FlxG.hpp"

#include "flixel++/FlxLog.hpp"
#include "flixel++/FlxMacros.hpp"

#include "assets/vcr.h"
#include "assets/cursor.h"

#ifdef FLIXEL_SDL
#ifdef SDL_LEGACY
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "flixel++/SDL_Backports.hpp"
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif
#endif

using Flx::Globals::game, Flx::Globals::width, Flx::Globals::height;

#if defined(FLIXEL_SDL) || defined(FLIXEL_OPENGL)
inline void gameEvents(SDL_Window *window)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
#ifndef SDL_LEGACY
            if (e.key.repeat == 0)
#endif
                Flx::Globals::keys->keys[e.key.keysym.sym % 255] = true;
            break;
        case SDL_KEYUP:
            Flx::Globals::keys->keys[e.key.keysym.sym % 255] = false;
            break;
#ifndef SDL_LEGACY
        case SDL_WINDOWEVENT:
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
                SDL_GetWindowSize(window, &Flx::Globals::width, &Flx::Globals::height);
                game->curState->onResize(Flx::Globals::width, Flx::Globals::height);
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                game->paused = false;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                game->paused = true;
                break;
            }
            break;
#endif
        case SDL_QUIT:
            game->quitting = true;
            break;
        default:
            break;
        }
    }
}
#endif

#ifdef FLIXEL_SDL

// -------------------------------------
Flx::Backends::SDL::SDL()
    : window(nullptr),
      renderer(nullptr)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

#ifdef SDL_LEGACY
    window = SDL_SetVideoMode(width, height, 0, 0);
    SDL_WM_SetCaption(title, NULL);
    SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 0));
#else
    window = SDL_CreateWindow(game->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_SetWindowResizable(window, SDL_TRUE);
#endif

    SDL_ShowCursor(1);

    SDL_RWops *rw = SDL_RWFromConstMem((void *)vcr_ttf, vcr_ttf_size);
    Flx::Assets::defaultFont = TTF_OpenFontRW(rw, 1, 24);

    SDL_Surface *temp = IMG_LoadPNG_RW(SDL_RWFromConstMem((void *)cursor_png, cursor_png_size));

#ifdef SDL_LEGACY
    Flx::Assets::defaultCursor = temp;
#else
    Flx::Assets::defaultCursor = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);

    trace("Loaded SDL");
#endif
}

Flx::Backends::SDL::~SDL()
{
#ifdef SDL_LEGACY
    SDL_FreeSurface(window);
#else
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
#endif
    TTF_Quit();
}

Flx::Graphic *Flx::Backends::SDL::requestTexture(const char *path)
{
    SDL_Surface *img = IMG_Load(path);
    if (!img)
    {
        Flx::Log::warn(SDL_GetError());
        return nullptr;
    }
    return requestTexture(img);
}

bool Flx::Backends::SDL::deleteTexture(void *tex)
{
    SDL_DestroyTexture((SDL_Texture *)tex);
    return true;
}

Flx::Graphic *Flx::Backends::SDL::requestTexture(const void *data, const size_t size)
{
    return requestTexture(IMG_Load_RW(SDL_RWFromConstMem(data, size), 0));
}

Flx::Graphic *Flx::Backends::SDL::requestTexture(SDL_Surface *surface)
{
    Flx::Graphic *tex = new Flx::Graphic(surface->w, surface->h, (void *)SDL_CreateTextureFromSurface(renderer, surface));
    SDL_FreeSurface(surface);
    return tex;
}

Flx::Graphic *Flx::Backends::SDL::requestText(const char *text)
{
    return requestTexture(TTF_RenderText_Solid((TTF_Font *)Flx::Assets::defaultFont, text, {255, 255, 255, 255}));
}

Flx::Graphic *Flx::Backends::SDL::requestRectangle(float width, float height, int color)
{
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    auto textemp = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask, bmask, amask);
    SDL_FillRect(textemp, nullptr, color);

    return requestTexture(textemp);
}

void Flx::Backends::SDL::runEvents()
{
    gameEvents(window);
}

inline const SDL_FRect toSDLFRect(Flx::Rect &rect)
{
    return SDL_FRect{
        rect.x, rect.y, rect.width, rect.height};
}

inline const SDL_Rect toSDLRect(Flx::Rect &rect)
{
    return SDL_Rect{
        (Sint16)rect.x, (Sint16)rect.y, (Uint16)rect.width, (Uint16)rect.height};
}

inline const SDL_FPoint toSDLFPoint(Flx::Point &rect)
{
    return SDL_FPoint{
        rect.x, rect.y};
}

void Flx::Backends::SDL::update()
{
#ifdef SDL_LEGACY
    game->curState->update();
    SDL_FillRect(window, NULL, 0x000000);
    game->curState->draw();
    SDL_Flip(window);
#else
    game->curState->update();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    game->curState->draw();
    SDL_RenderPresent(renderer);
#endif
}

void Flx::Backends::SDL::render(Flx::Sprite *spr)
{
    SDL_Rect stuff = toSDLRect(spr->clipRect);
    if (spr->animation->animated)
    {
        auto anim = spr->animation->getCurAnim();
        stuff.x = anim->x;
        stuff.y = anim->y;
        stuff.w = anim->width;
        stuff.h = anim->height;
    }
#ifdef SDL_LEGACY
    SDL_Rect dst = SDL_Rect{
        (Sint16)spr->x - (Sint16)(spr->width / 2),
        (Sint16)spr->y - (Sint16)(spr->height / 2),
        (Uint16)spr->width * (Uint16)spr->scale.x,
        (Uint16)spr->height * (Uint16)spr->scale.y};

    // SDL_SetAlpha(graphic->bitmap, SDL_SRCALPHA, 255 - (alpha % 101) * 255 / 100);
    SDL_UpperBlitScaled(graphic->bitmap, NULL, Flx::Globals::game->window, &dst);
#else
    SDL_FRect dst = SDL_FRect{
        spr->x - (spr->width / 2),
        spr->y - (spr->height / 2),
        spr->width * spr->scale.x,
        spr->height * spr->scale.y};

    auto originF = toSDLFPoint(spr->origin);
    SDL_SetTextureAlphaMod((SDL_Texture *)spr->graphic->bitmap, (spr->alpha % 101) * 255 / 100);
    SDL_RenderCopyExF(renderer, (SDL_Texture *)spr->graphic->bitmap, &stuff, &dst, spr->angle, &originF, SDL_FLIP_NONE);
#endif
}

uint32_t Flx::Backends::SDL::getTicks()
{
    return SDL_GetTicks();
}

void Flx::Backends::SDL::delay(uint32_t ms)
{
    SDL_Delay(ms);
}

Flx::Shader *Flx::Backends::SDL::compileShader(Flx::Shader *shader)
{
    return nullptr; // shaders are unsupported
}

#endif