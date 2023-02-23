#include "flixel++/FlxSprite.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxColor.hpp"
#include "flixel++/FlxLog.hpp"
#include "flixel++/FlxUtils.hpp"

Flx::Sprite::Sprite(float x, float y)
    : Object(x, y), 
    alpha(100),
    angle(0),
    visible(true),
    graphic(nullptr),
    clipRect(0, 0, 0, 0), 
    hitbox(0, 0, 0, 0), 
    animation(new Flx::AnimationController),
    color(255, 255, 255, 255),
    offset(0, 0),
    scale(1, 1),
    origin(x, y)
{
}

Flx::Sprite::Sprite(const char* path)
    : Sprite(0,0)
{
    loadGraphic(path);
}

Flx::Sprite::Sprite()
    : Sprite(0,0)
{

};

Flx::Sprite::~Sprite()
{
    delete graphic;
    delete animation;
}

Flx::Sprite* Flx::Sprite::loadGraphic(const char* path) 
{
    if(!Flx::Utils::fileExists(path)){
        Flx::Log::warn(path);
        return nullptr;
    }
    graphic = Flx::Globals::game->backend->requestTexture(path);
    updatePosition();
    return this;
}

Flx::Sprite* Flx::Sprite::loadGraphic(const void* data, const size_t size)
{
    graphic = Flx::Globals::game->backend->requestTexture(data, size);
    updatePosition();
    return this;
}

Flx::Sprite* Flx::Sprite::makeGraphic(float width, float height, int color)
{
    graphic = Flx::Globals::game->backend->requestRectangle(width, height, color);
    updatePosition();
    return this;
}

bool Flx::Sprite::collides(Flx::Sprite* sprite)
{
    return true;
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
    if(!graphic)
        return;
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
    origin.set(width/2, height/2);
}

void Flx::Sprite::update() {
    if(animation->animated)
    {
        animation->frameIndex++;
        animation->frameIndex = (Flx::Globals::game->backend->getTicks() / (animation->curAnim->fps)) % animation->curAnim->size();
    }
}

void Flx::Sprite::draw() {
    if(!graphic || !visible)
        return;
    Flx::Globals::game->backend->render(this);
}