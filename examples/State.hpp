#pragma once
#include "flixel++/FlxState.hpp"
#include "flixel++/FlxSprite.hpp"
#include "flixel++/FlxSound.hpp"

class PlayState : public Flx::State
{
    public:
    PlayState(){};
    ~PlayState(){};
    Flx::Sprite* sprite;
    float time = 0.0f;
    void create(){
        sprite = new Flx::Sprite(0,0);
        sprite->loadGraphic("assets/logo.png");
        sprite->setGraphicSize(240,240);
        sprite->screenCenter();
        add(sprite);
    };
    virtual void update(){
        sprite->x += cos(time);
        sprite->y += sin(time);
        time += 0.05f;
        Flx::State::update();
    }
};