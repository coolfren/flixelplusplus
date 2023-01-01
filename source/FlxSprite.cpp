#include "flixel++/FlxSprite.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxColor.hpp"

Flx::Sprite::Sprite(float x, float y)
    : Object(x, y), 
    alpha(100),
    clipRect(0, 0, 0, 0), 
    hitbox(0, 0, 0, 0), 
    animation(new Flx::AnimationController),
    offset(0, 0),
    scale(1, 1),
    origin(x, y)
{
}

Flx::Sprite::~Sprite()
{
    delete graphic;
    delete animation;
}

Flx::Sprite* Flx::Sprite::loadGraphic(const char* path) {
    graphic = Flx::Graphic::loadFromPath(path);
    updatePosition();
    return this;
}

Flx::Sprite* Flx::Sprite::makeGraphic(float width, float height, int color)
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
    
    #ifdef SDL_LEGACY
    auto tex = textemp;
    #else
    auto tex = SDL_CreateTextureFromSurface(Flx::Globals::_curGame->renderer, textemp);
    #endif

    graphic = new Flx::Graphic(width, height, tex);
    updatePosition();
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

void Flx::Sprite::updatePosition()
{
    this->width = graphic->width;
    this->height = graphic->height;
    this->clipRect.width = graphic->width;
    this->clipRect.height = graphic->height;
}

void Flx::Sprite::updateHitbox()
{
    hitbox.x = x;
    hitbox.y = y;
    hitbox.width = width;
    hitbox.height = height;
}

void Flx::Sprite::update() {
    if(animation->animated)
    {
        animation->frameIndex++;
        animation->frameIndex = (SDL_GetTicks() / (animation->curAnim->fps)) % animation->curAnim->size();
    }
}

void Flx::Sprite::draw() {
#ifdef SDL_LEGACY
    SDL_Rect dst = SDL_Rect{
        (Sint16)x - (Sint16)(width / 2),
        (Sint16)y - (Sint16)(height / 2),
        (Uint16)width * (Uint16)scale.x,
        (Uint16)height * (Uint16)scale.y
    };

    SDL_SetSurfaceAlphaMod(graphic->bitmap, (alpha % 101) * 255 / 100);
    SDL_UpperBlitScaled(graphic->bitmap, NULL, Flx::Globals::_curGame->window, &dst);
#else
    SDL_FRect dst = SDL_FRect{
        //NEED TO CHANGE IT LATER IF RECUSED
        x - (width / 2),
        y - (height / 2), 
        width * scale.x, 
        height * scale.y
    };
    auto stuff = clipRect.toSDLRect();
    if(animation->animated)
    {
        auto anim = animation->getCurAnim();
        stuff.x = anim->x;
        stuff.y = anim->y;
        stuff.w = anim->width;
        stuff.h = anim->height;
    }

    SDL_SetTextureAlphaMod(graphic->bitmap, (alpha % 101) * 255 / 100);
    SDL_RenderCopyF(Flx::Globals::_curGame->renderer, graphic->bitmap, &stuff, &dst);
#endif
}
