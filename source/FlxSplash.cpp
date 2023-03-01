#include "flixel++/FlxSplash.hpp"
#include "assets/logoGreen.h"
#include "assets/logoBlue.h"
#include "assets/logoCyan.h"
#include "assets/logoYellow.h"
#include "assets/logoRed.h"
#include "assets/logoC.h"
#include "flixel++/FlxMacros.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxColor.hpp"
#include "flixel++/FlxLog.hpp"

int elapsedTime = 0;
int result = 0;
const char flixel[8] = {'F','l','i','x','e','l','+','+'};

Flx::Splash::Splash(Flx::State* state)
    : nextState(state)
{

}

void Flx::Splash::create()
{

    yellow = new Flx::Sprite(0, 0);

    yellow->loadGraphic((void *)logoYellow_png, logoYellow_png_length);
    yellow->setGraphicSize((yellow->graphic->width / 9), (yellow->graphic->height / 9));
    add(yellow);
    yellow->screenCenter();
    yellow->visible = false;

    red = new Flx::Sprite(0, 0);
    red->loadGraphic((void *)logoRed_png, logoRed_png_length);
    red->setGraphicSize((red->graphic->width / 9), (red->graphic->height / 9) + 3);
    add(red);
    red->screenCenter();
    red->visible = false;


    blue = new Flx::Sprite(0, 0);
    blue->loadGraphic((void *)logoBlue_png, logoBlue_png_length);
    blue->setGraphicSize((blue->graphic->width / 9), (blue->graphic->height / 9) +2 );
    add(blue);
    blue->screenCenter();
    blue->visible = false;

    cyan = new Flx::Sprite(0, 0);
    cyan->loadGraphic((void *)logoCyan_png, logoCyan_png_length);
    cyan->setGraphicSize((cyan->graphic->width / 9), (cyan->graphic->height / 9));
    add(cyan);
    cyan->screenCenter();
    cyan->visible = false;


    green = new Flx::Sprite(0, 0);
    green->loadGraphic((void *)logoGreen_png, logoGreen_png_length);
    green->setGraphicSize((green->graphic->width / 9) + 5, (green->graphic->height / 9) + 5);
    add(green);
    green->screenCenter();

    cpp = new Flx::Sprite(0, 0);
    cpp->loadGraphic((void *)logoC_png, logoC_png_length);
    cpp->setGraphicSize((cpp->graphic->width / 9), (cpp->graphic->height / 9));
    add(cpp);
    cpp->screenCenter();
    cpp->visible = true;
    cpp->alpha = 0;

    flixelText = new Text(0,0,"");
    flixelText->screenCenter();
    flixelText->y += 150;
    add(flixelText);

    //flixelSound = new Flx::Sound();
    //flixelSound->load("assets/sounds/flixel.ogg");
    //flixelSound->play();
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

    if(elapsedTime >= 37){
        green->visible = true;
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
    if(elapsedTime >= 330){
        Flx::Globals::switchState(nextState);
    }
}

