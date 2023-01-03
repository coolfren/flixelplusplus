#ifndef FLXG_HPP
#define FLXG_HPP
#include "flixel++/FlxGame.hpp"
#include "flixel++/FlxKeyboard.hpp"
#include "flixel++/FlxMouse.hpp"

namespace Flx
{
    namespace Globals
    {
        extern float width, height;

        extern Flx::Game* _curGame;

        extern Flx::Random* random;

        extern Flx::SoundManager* sound;

        extern Flx::Keyboard* keys;

        extern Flx::Mouse* mouse;

        extern bool switchState(Flx::State* state);
    }
}

#endif