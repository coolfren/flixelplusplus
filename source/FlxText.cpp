#include "flixel++/FlxText.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxAssets.hpp"
#include "flixel++/FlxMacros.hpp"

Flx::Text::Text(float x, float y, const std::string& text)
    : Flx::Sprite::Sprite(x,y)
{
    this->text = text;
    if(this->text == ""){
        this->text = " ";
    }

    this->font = Flx::Assets::defaultFont;

    this->drawText();

    updatePosition();
}

Flx::Text::~Text()
{
    Flx::Sprite::~Sprite();
}

void Flx::Text::setText(std::string newText){
    this->text = newText;
    drawText();
    updatePosition();
}

void Flx::Text::drawText()
{
    if(graphic != nullptr)
        delete graphic;
    graphic = Flx::Globals::game->backend->requestText(text.c_str());
}
