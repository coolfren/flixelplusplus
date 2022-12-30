#include "flixel++/FlxText.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxAssets.hpp"
#include "flixel++/FlxMacros.hpp"

Flx::Text::Text(float x, float y, const std::string& text)
    : Flx::Sprite::Sprite(x,y)
{
    this->text = text;
    this->font = Flx::Assets::defaultFont;
    this->color = {255,255,255,255};

    this->drawText();
    /*auto ttf = TTF_RenderText_Solid(Flx::Assets::defaultFont, text.c_str(), {255,255,255,255});
    graphic = Flx::Graphic::loadFromSurface(ttf);*/
    updatePosition();
}

Flx::Text::~Text()
{
}

void Flx::Text::setText(std::string newText){
    this->text = newText;
    trace(this->text);
    drawText();
}

void Flx::Text::drawText()
{
    auto ttf = TTF_RenderText_Solid(Flx::Assets::defaultFont, text.c_str(), {255,255,255,255});
    Flx::Sprite::graphic = Flx::Graphic::loadFromSurface(ttf);
}
