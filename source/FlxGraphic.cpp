#include "flixel++/FlxGraphic.hpp"
#include "flixel++/FlxGame.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxLog.hpp"

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

uint32_t Flx::Graphic::getPixel32(int x, int y){
    return 0;
}

Flx::Graphic* Flx::Graphic::loadFromPath(const char* path){
    SDL_Surface* img = IMG_Load(path);
    if(!img){
        Flx::Log::warn(SDL_GetError());
        return nullptr;
    }
    return loadFromSurface(img);
}

Flx::Graphic* Flx::Graphic::loadFromRAWPath(SDL_RWops* raw){
    return loadFromSurface(IMG_Load_RW(raw,0));
}


Flx::Graphic* Flx::Graphic::loadFromSurface(SDL_Surface* surface){
    #ifdef SDL_LEGACY
    auto temp = surface;
    #else
    //auto temp = SDL_CreateTextureFromSurface(Flx::Globals::game->renderer, surface);
    SDL_FreeSurface(surface);
    #endif

    //Flx::Graphic* a = new Flx::Graphic(surface->w, surface->h, temp);
    return NULL;
}