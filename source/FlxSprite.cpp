#include "flixel++/FlxSprite.hpp"
#include "flixel++/FlxG.hpp"

Flx::Sprite::Sprite(float x, float y)
    : Object(x,y)
{
    
}

Flx::Sprite::~Sprite()
{
    delete graphic;
}

Flx::Sprite* Flx::Sprite::loadGraphic(const char* path){
    graphic = Flx::Graphic::loadFromPath(path);
    this->width = graphic->width;
    this->height = graphic->height;
    return this;
}

void Flx::Sprite::update(){

}

void Flx::Sprite::draw(){
    #ifdef SDL_LEGACY
    SDL_Rect dst = SDL_Rect{
        (Sint16)x,(Sint16)y,(Uint16)width,(Uint16)height
    };
    SDL_BlitSurface(graphic->bitmap, NULL, Flx::Globals::_curGame->window, &dst);
    #else
    SDL_FRect dst = SDL_FRect{
        x,y,width,height
    };
    SDL_RenderCopyF(Flx::Globals::_curGame->renderer, graphic->bitmap, NULL, &dst);
    #endif
}