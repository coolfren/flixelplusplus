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
    SDL_Rect tempQ{0,0,0,0};
    #ifdef SDL_LEGACY
    Bitmap* temp = IMG_Load(path);
    tempQ.w = temp->w;
    tempQ.h = temp->h;
    #else
    Bitmap* temp = IMG_LoadTexture(Flx::Globals::_curGame->renderer, path);
    SDL_QueryTexture(temp, NULL, NULL, &tempQ.w, &tempQ.h);
    #endif

    Flx::Graphic* a = new Flx::Graphic(tempQ.w, tempQ.h, temp);
    return a;
}