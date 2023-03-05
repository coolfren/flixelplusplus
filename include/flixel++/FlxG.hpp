#ifndef FLXG_HPP
#define FLXG_HPP
#include "flixel++/FlxGame.hpp"
#include "flixel++/FlxKeyboard.hpp"
#include "flixel++/FlxMouse.hpp"

namespace Flx
{
    /**
     * Globals helper class for RNG, sound, keys, gameinfo etc.
    */
    namespace Globals
    {
        extern int width, height;

        extern Flx::Game* game;

        extern Flx::Random* random;

        extern Flx::SoundManager* sound;

        extern Flx::Keyboard* keys;

        extern Flx::Mouse* mouse;

        extern bool switchState(Flx::State* state);
    }
}

#endif