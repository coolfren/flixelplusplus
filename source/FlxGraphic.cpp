#include "flixel++/FlxGraphic.hpp"
#include "flixel++/FlxGame.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxLog.hpp"
#include "flixel++/FlxColor.hpp"
#include "flixel++/FlxMacros.hpp"

int Flx::Graphic::currentID = 0;

Flx::Graphic::Graphic(int width, int height, void* tex)
    : width(width), height(height), bitmap(tex),id(currentID++)
{
    trace(id);
}

Flx::Graphic::~Graphic(){
    Flx::Globals::game->backend->deleteTexture(bitmap);
};

Flx::Color Flx::Graphic::getPixel32(int x, int y){
    uint8_t* colors = (uint8_t*)bitmap + (y * width + x) * 4;
    return Flx::Color(
        colors[0],
        colors[1],
        colors[2],
        colors[3]
    );
}