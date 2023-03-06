#pragma once
#include <flixel++/FlxState.hpp>
#include <flixel++/FlxSprite.hpp>

class PlayState : public Flx::State
{
    public:
    PlayState(){};
    ~PlayState(){};
    void create(){
        Flx::Sprite* logo = new Flx::Sprite(0, 0);
        logo->loadGraphic("assets/logo.png");
        logo->screenCenter();
        add(logo);
    }
    void update(){
        Flx::State::update();
    }
};