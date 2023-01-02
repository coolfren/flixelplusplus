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
    if (enable)
    {
        SDL_Rect dest = {this->x, this->y, clipRect.width, clipRect.height};

        auto src = clipRect.toSDLRect();

        #ifdef SDL_LEGACY
        SDL_UpperBlitScaled(cursor, &src, Flx::Globals::_curGame->window, &dest);
        #else
        SDL_RenderCopy(Flx::Globals::_curGame->renderer, cursor, &src, &dest);
        #endif
    }
}

void Flx::Mouse::setGraphic()
{
    #ifdef SDL_LEGACY
    clipRect = {0, 0, cursor->w, cursor->h};
    #else
    Flx::Point size;
    SDL_QueryTexture(cursor, NULL, NULL, &size.w, &size.h);

    clipRect = {0, 0, size.w, size.h};
    #endif
}

void Flx::Mouse::loadGraphic(const char* path)
{
    #ifdef SDL_LEGACY
    cursor = IMG_Load(path);
    #else
    auto surface = IMG_Load(path);
    cursor = SDL_CreateTextureFromSurface(Flx::Globals::_curGame->renderer, surface);
    SDL_FreeSurface(surface);
    #endif
    setGraphic();
}

void Flx::Mouse::update()
{
    if (enable)
    {
        SDL_GetMouseState(&pos._x, &pos._y);
        this->x = pos._x;
        this->y = pos._y;
    }
}