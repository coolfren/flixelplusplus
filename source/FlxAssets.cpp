#include "flixel++/FlxG.hpp"
#include "flixel++/FlxAssets.hpp"
#include "flixel++/FlxMacros.hpp"
#include "vcr.h"
#include "logoC.h"


TTF_Font* Flx::Assets::defaultFont = nullptr;
Bitmap* Flx::Assets::defaultCursor = nullptr;

void Flx::Assets::initialize(){
    SDL_RWops* rw = SDL_RWFromConstMem((void*)vcr_ttf, vcr_ttf_size);
    defaultFont = TTF_OpenFontRW(rw, 1, 24);

    auto temp = IMG_Load("assets/images/ui/cursor.png");

    #ifdef SDL_LEGACY
    defaultCursor = IMG_Load("assets/ui/cursor.png");
    #else
    auto temp = IMG_Load("assets/ui/cursor.png");

    defaultCursor = SDL_CreateTextureFromSurface(Flx::Globals::_curGame->renderer, temp);
    SDL_FreeSurface(temp);
    #endif
}