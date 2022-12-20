#pragma once
#include "flixel++/FlxState.hpp"
#include "flixel++/FlxSprite.hpp"
#include "flixel++/FlxSound.hpp"
#include "flixel++/FlxNet.hpp"
#include "flixel++/FlxText.hpp"
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

        trace("ok");

        auto text = new Flx::Text(0,0, "i am a piece of text!");
        text->screenCenter();
        add(text);
    };
    virtual void update(){
        sprite->x += cos(time);
        sprite->y += sin(time);
        time += 0.05f;
        Flx::State::update();
    }
};