#include "flixel++/FlxG.hpp"
#include "flixel++/FlxAssets.hpp"
#include "flixel++/FlxMacros.hpp"
#include "assets/vcr.h"
#include "assets/logoC.h"
#include "assets/cursor.h"

TTF_Font* Flx::Assets::defaultFont = nullptr;
Bitmap* Flx::Assets::defaultCursor = nullptr;

void Flx::Assets::initialize(){
    SDL_RWops* rw = SDL_RWFromConstMem((void*)vcr_ttf, vcr_ttf_size);
    defaultFont = TTF_OpenFontRW(rw, 1, 24);

    auto temp = IMG_LoadPNG_RW(SDL_RWFromConstMem((void*)cursor_png, cursor_png_size));

    #ifdef SDL_LEGACY
    defaultCursor = temp;
    #else
    //defaultCursor = SDL_CreateTextureFromSurface(Flx::Globals::game->renderer, temp);
    SDL_FreeSurface(temp);
    #endif
}