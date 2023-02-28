#include "flixel++/FlxGraphic.hpp"
#include "flixel++/FlxGame.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxLog.hpp"

int Flx::Graphic::currentID = 0;

Flx::Graphic::Graphic(int width, int height, void* tex)
    : width(width), height(height), bitmap(tex)
{
    #ifdef FLIXEL_OPENGL
        id = currentID++;
    #endif
}

Flx::Graphic::~Graphic(){
    Flx::Globals::game->backend->deleteTexture(bitmap);
};

uint32_t Flx::Graphic::getPixel32(int x, int y){
    return 0;
}