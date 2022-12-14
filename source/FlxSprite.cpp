#include "flixel++/FlxSprite.hpp"
#include "flixel++/FlxG.hpp"

Flx::Sprite::Sprite(float x, float y)
    : Object(x,y), clipRect(0,0,0,0), hitbox(0,0,0,0)
{
    origin = Point(0, 0);
    offset = Point(0, 0);
    scale = Point(1, 1);
}

Flx::Sprite::~Sprite()
{
    delete graphic;
}

Flx::Sprite* Flx::Sprite::loadGraphic(const char* path){
    graphic = Flx::Graphic::loadFromPath(path);
    this->width = graphic->width;
    this->height = graphic->height;
    this->clipRect.width = graphic->width;
    this->clipRect.height = graphic->height;
    return this;
}

void Flx::Sprite::setGraphicSize(float width, float height)
{
    this->width = width;
    this->height = height;
    updateHitbox();
}

void Flx::Sprite::screenCenter()
{
    x = (Flx::Globals::width / 2);
    y = (Flx::Globals::height / 2);
}
void Flx::Sprite::updateHitbox()
{
    hitbox.x = x;
    hitbox.y = y;
    hitbox.width = width;
    hitbox.height = height;
    origin.x = -(width / 2);
    origin.y = -(height / 2);
}

void Flx::Sprite::update(){

}

void Flx::Sprite::draw(){
    #ifdef SDL_LEGACY
    SDL_Rect dst = SDL_Rect{
        (Sint16)x + origin.x,(Sint16)y + origin.y,(Uint16)width * scale.x,(Uint16)height * scale.y
    };
    SDL_BlitSurface(graphic->bitmap, NULL, Flx::Globals::_curGame->window, &dst);
    #else
    SDL_FRect dst = SDL_FRect{
        x + origin.x,y + origin.y,width * scale.x,height * scale.y
    };
    auto stuff = clipRect.toSDLRect();
    SDL_RenderCopyF(Flx::Globals::_curGame->renderer, graphic->bitmap, &stuff, &dst);
    #endif
}