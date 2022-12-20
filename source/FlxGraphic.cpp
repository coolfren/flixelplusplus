#include "flixel++/FlxGraphic.hpp"
#include "flixel++/FlxGame.hpp"
#include "flixel++/FlxG.hpp"

Flx::Graphic::Graphic(int width, int height, Bitmap* tex)
    : width(width), height(height), bitmap(tex)
{
    
}

Flx::Graphic::~Graphic(){
    #ifdef SDL_LEGACY
    SDL_FreeSurface(bitmap);
    #else
    SDL_DestroyTexture(bitmap);
    #endif
};

Flx::Graphic* Flx::Graphic::loadFromPath(const char* path){
    return loadFromSurface(IMG_Load(path));
}

Flx::Graphic* Flx::Graphic::loadFromSurface(SDL_Surface* surface){
    SDL_Rect tempQ{0,0,0,0};
    tempQ.w = surface->w;
    tempQ.h = surface->h;
    #ifdef SDL_LEGACY
    auto temp = surface;
    #else
    auto temp = SDL_CreateTextureFromSurface(Flx::Globals::_curGame->renderer, surface);
    SDL_FreeSurface(surface);
    #endif

    Flx::Graphic* a = new Flx::Graphic(tempQ.w, tempQ.h, temp);
    return a;
}