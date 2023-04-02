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
#include "assets/logoBlue.h"

class PlayState : public Flx::State
{
public:
    PlayState(){};
    ~PlayState(){};
    Flx::Sprite *saul;
    Flx::Sprite *finger;
    Flx::Sprite *waltuh;
    Flx::Sprite *jessy;
    Flx::Sprite *mik;

    Flx::Text *text;
    Flx::Http *http;
    Flx::Sound* flixelSound;

    float time = 0.0f;
    float offsetX = 0.0f, offsetY = 0.0f;
    void create()
    {
        Flx::Globals::bgColor = Flx::Color(207, 105, 4,0);

        http = new Flx::Http("https://pastebin.com/raw/j9cs4GWP");
        trace(http->storage);


        finger = new Flx::Sprite(1600, 300);
        if (http->storage == "saul goodman")
        {
            finger->loadGraphic("assets/finger.png");
            finger->setGraphicSize(120, 160);
        }
        else
        {
            finger->loadGraphic("assets/logo.png");
            finger->setGraphicSize(240, 240);
        }
        add(finger);

        waltuh = new Flx::Sprite(100, 600);
        if (http->storage == "saul goodman")
        {
            waltuh->loadGraphic("assets/waltuh.png");
            waltuh->setGraphicSize(180, 260);
        }
        else
        {
            waltuh->loadGraphic("assets/logo.png");
            waltuh->setGraphicSize(240, 240);
        }
        add(waltuh);

        jessy = new Flx::Sprite(300, 610);
        if (http->storage == "saul goodman")
        {
            jessy->loadGraphic("assets/jesse.png");
            jessy->setGraphicSize(180, 260);
        }
        else
        {
            jessy->loadGraphic("assets/logo.png");
            jessy->setGraphicSize(240, 240);
        }
        add(jessy);

        mik = new Flx::Sprite(1800, 210);
        if (http->storage == "saul goodman")
        {
            mik->loadGraphic("assets/mikuh.png");
            mik->setGraphicSize(180, 260);
        }
        else
        {
            mik->loadGraphic("assets/logo.png");
            mik->setGraphicSize(240, 240);
        }
        add(mik);


        saul = new Flx::Sprite(0, 0);
        if (http->storage == "saul goodman")
        {
            saul->loadGraphic("assets/Saul.png");
            saul->setGraphicSize(820, 1020);
        }
        else
        {
            saul->loadGraphic("assets/logo.png");
            saul->setGraphicSize(240, 240);
        }

        saul->screenCenter();
        add(saul);

        /*text = new Flx::Text(0, 100, "i am a piece of text!");
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
        add(text);*/

        /*if (http->storage == "saul goodman")
        {
            Flx::Globals::mouse->loadGraphic("assets/troll.png");
        }*/

        flixelSound = new Flx::Sound();
        flixelSound->load("assets/beatbox.ogg");
        flixelSound->play();

    };
    virtual void update()
    {
        saul->x += sin(time) + offsetX * 2;
        finger->y += cos(time * 10) + offsetX * 2;
        mik->y += cos(time * 9.4) + offsetX * 2;
        saul->width += 3 * sin(time) + offsetX * 2;
        saul->height += 3 * cos(time) + offsetY * 2;
        waltuh->width += 10 * sin(time) + offsetX * 2;
        jessy->width += 10 * sin(time * 1.4) + offsetX * 2;
        /*text->x -= cos(time) - offsetX * 2;
        text->y -= sin(time) - offsetY * 2;*/

        time += 0.05f;

        Flx::State::update();
    }
};