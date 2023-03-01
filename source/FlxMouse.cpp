#include "flixel++/FlxMouse.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxPoint.hpp"
#include "flixel++/FlxMacros.hpp"

Flx::Mouse::Mouse()
{
    cursor = Flx::Assets::defaultCursor;
    enable = true;
    setGraphic();

    this->x = Flx::Globals::width / 2;
    this->y = Flx::Globals::height / 2;
}

Flx::Mouse::~Mouse(){
    
}

void Flx::Mouse::draw()
{
    if (!enable)
        return;
    /*
    SDL_Rect dest = {
        static_cast<int>(this->x), 
        static_cast<int>(this->y), 
        static_cast<int>(clipRect.width), 
        static_cast<int>(clipRect.height)
    };
    */
    //auto src = clipRect.toSDLRect();

    #ifdef SDL_LEGACY
    SDL_UpperBlitScaled(cursor, &src, Flx::Globals::game->window, &dest);
    #else
    //SDL_RenderCopy(Flx::Globals::game->renderer, cursor, &src, &dest);
    #endif
}

void Flx::Mouse::setGraphic()
{
    #ifdef SDL_LEGACY
    clipRect = {0, 0, cursor->w, cursor->h};
    #else
    Flx::Point size;
    //SDL_QueryTexture(cursor, NULL, NULL, &size.w, &size.h);

    clipRect = {0, 0, static_cast<float>(size.w), static_cast<float>(size.h)};
    #endif
}

void Flx::Mouse::loadGraphic(const char* path)
{
    #ifdef SDL_LEGACY
    cursor = IMG_Load(path);
    #else
    //auto surface = IMG_Load(path);
    //cursor = SDL_CreateTextureFromSurface(Flx::Globals::game->renderer, surface);
    //SDL_FreeSurface(surface);
    #endif
    setGraphic();
}

void Flx::Mouse::update()
{
    if (enable)
    {
        //SDL_GetMouseState(&pos._x, &pos._y);
        this->x = pos._x;
        this->y = pos._y;
    }
}