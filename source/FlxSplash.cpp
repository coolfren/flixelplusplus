#include "flixel++/FlxSplash.hpp"
#include "logoGreen.h"
#include "logoBlue.h"
#include "logoCyan.h"
#include "logoYellow.h"
#include "logoRed.h"
#include "logoC.h"
#include "flixel++/FlxMacros.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxColor.hpp"

SDL_RWops *raw = nullptr;
int elapsedTime = 0;
int result = 0;
const char flixel[8] = {'F','l','i','x','e','l','+','+'};

void Flx::Splash::create()
{

    yellow = new Flx::Sprite(0, 0);
    raw = SDL_RWFromConstMem((void *)logoYellow_png, logoYellow_png_length);
    yellow->loadRAWGraphic(raw);
    yellow->setGraphicSize((yellow->graphic->width / 9), (yellow->graphic->height / 9));
    add(yellow);
    yellow->screenCenter();
    yellow->visible = false;

    red = new Flx::Sprite(0, 0);
    raw = SDL_RWFromConstMem((void *)logoRed_png, logoRed_png_length);
    red->loadRAWGraphic(raw);
    red->setGraphicSize((red->graphic->width / 9), (red->graphic->height / 9) + 3);
    add(red);
    red->screenCenter();
    red->visible = false;


    blue = new Flx::Sprite(0, 0);
    raw = SDL_RWFromConstMem((void *)logoBlue_png, logoBlue_png_length);
    blue->loadRAWGraphic(raw);
    blue->setGraphicSize((blue->graphic->width / 9), (blue->graphic->height / 9) +2 );
    add(blue);
    blue->screenCenter();
    blue->visible = false;

    cyan = new Flx::Sprite(0, 0);
    raw = SDL_RWFromConstMem((void *)logoCyan_png, logoCyan_png_length);
    cyan->loadRAWGraphic(raw);
    cyan->setGraphicSize((cyan->graphic->width / 9), (cyan->graphic->height / 9));
    add(cyan);
    cyan->screenCenter();
    cyan->visible = false;


    green = new Flx::Sprite(0, 0);
    raw = SDL_RWFromConstMem((void *)logoGreen_png, logoGreen_png_length);
    green->loadRAWGraphic(raw);
    green->setGraphicSize((green->graphic->width / 9) + 5, (green->graphic->height / 9) + 5);
    add(green);
    green->screenCenter();

    cpp = new Flx::Sprite(0, 0);
    raw = SDL_RWFromConstMem((void *)logoC_png, logoC_png_length);
    cpp->loadRAWGraphic(raw);
    cpp->setGraphicSize((cpp->graphic->width / 9), (cpp->graphic->height / 9));
    add(cpp);
    cpp->screenCenter();
    cpp->visible = true;
    cpp->alpha = 0;

    flixelText = new Text(0,0,"");
    flixelText->screenCenter();
    flixelText->y += 150;
    add(flixelText);

    flixelSound = new Flx::Sound();
    flixelSound->load("assets/sounds/flixel.ogg");
    flixelSound->play();
}

void Flx::Splash::update()
{
    if(elapsedTime >= 7){
        yellow->visible = true;
    }
    if(elapsedTime >= 14){
        red->visible = true;
    }
    if(elapsedTime >= 21){
        blue->visible = true;
    }
    if(elapsedTime >= 28){
        cyan->visible = true;
    }

    if(elapsedTime >= 100 && elapsedTime <= 140 && elapsedTime % 5 == 0){
        flixelText->setText(flixelText->text + flixel[(elapsedTime - 100) / 5]);
    }

    elapsedTime += 1;
    if(cpp->alpha < 100 && elapsedTime < 200 )
        cpp->alpha += 2.5;

    if(elapsedTime >= 200 && cpp->alpha > 0)
    {
        yellow->alpha -= 1;
        red->alpha -= 1;
        blue->alpha -= 1;
        cyan->alpha -= 1;
        green->alpha -= 1;
        cpp->alpha -= 1;
        flixelText->alpha -= 1;
    }
}

