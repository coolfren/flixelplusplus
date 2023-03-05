#pragma once
#include "flixel++/FlxState.hpp"
#include "flixel++/FlxSprite.hpp"
#include "flixel++/FlxAssets.hpp"
#include "flixel++/FlxSound.hpp"
#include "flixel++/FlxNet.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxText.hpp"
#include "flixel++/FlxMacros.hpp"
#include "flixel++/FlxHttp.hpp"
class PlayState : public Flx::State
{
public:
    PlayState(){};
    ~PlayState(){};
    Flx::Sprite *sprite;
    Flx::Text *text;
    Flx::Http *http;
    Flx::Sound* flixelSound;

    float time = 0.0f;
    float offsetX = 0.0f, offsetY = 0.0f;
    void create()
    {
        sprite = new Flx::Sprite(0, 0);

        sprite->loadGraphic("assets/Saul.png");
        sprite->setGraphicSize(800, 800);

        sprite->screenCenter();
        add(sprite);

        text = new Flx::Text(0, 100, "i am a piece of text!");
        add(text);
        
        flixelSound = new Flx::Sound();
        flixelSound->load("assets/flixel.ogg");
        flixelSound->play();

    };
    virtual void update()
    {
        sprite->x += cos(time) + offsetX * 2;
        sprite->y += sin(time) + offsetY * 2;
        text->x -= cos(time) - offsetX * 2;
        text->y -= sin(time) - offsetY * 2;

        time += 0.05f;

        Flx::State::update();
    }
};