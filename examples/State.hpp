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
        http = new Flx::Http("https://pastebin.com/raw/j9cs4GWP");
        trace(http->storage);

        sprite = new Flx::Sprite(0, 0);
        if (http->storage == "saul goodman")
        {
            sprite->loadGraphic("examples/assets/Saul.png");
            sprite->setGraphicSize(800, 800);
        }
        else
        {
            sprite->loadGraphic("assets/images/logo/logo.png");
            sprite->setGraphicSize(240, 240);
        }

        sprite->screenCenter();
        add(sprite);

        text = new Flx::Text(0, 100, "i am a piece of text!");
        if (http->storage == "saul goodman")
        {
            text->screenCenter();
            text->setText(http->storage + " V1.0");
        }
        else
        {
            text->x = (Flx::Globals::width / 2);
            text->setText("i am a piece of new text!");
        }
        add(text);

        if (http->storage == "saul goodman")
        {
            Flx::Globals::mouse->loadGraphic("examples/assets/troll.png");
        }

        flixelSound = new Flx::Sound();
        flixelSound->load("assets/sounds/flixel.ogg");
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