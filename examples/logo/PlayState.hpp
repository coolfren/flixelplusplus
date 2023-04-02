#pragma once
#include <flixel++/FlxState.hpp>
#include <flixel++/FlxSprite.hpp>
#include <flixel++/FlxMacros.hpp>

class PlayState : public Flx::State
{
public:
    Flx::Sprite *logo;
    float time;
    PlayState(){};
    ~PlayState(){};
    void create()
    {
        logo = new Flx::Sprite(0, 0);
        logo->loadGraphic("assets/logo.png");
        logo->screenCenter();
        add(logo);
        trace("Created");
    }
    void update()
    {
        logo->x += sin(time);
        logo->y += cos(time);
        logo->z += tan(time);
        time += 0.05;
        Flx::State::update();
    }
};