#include "flixel++/FlxAssets.hpp"
#include "vcr.h"

TTF_Font* Flx::Assets::defaultFont = nullptr;

void Flx::Assets::initialize(){
    SDL_RWops* rw = SDL_RWFromConstMem((void*)vcr_ttf, vcr_ttf_size);
    defaultFont = TTF_OpenFontRW(rw, 1, 24);
}