#ifndef FLXG_HPP
#define FLXG_HPP
#include "flixel++/FlxGame.hpp"

namespace Flx
{
    namespace Globals
    {
        extern float width, height;

        extern Flx::Game* _curGame;

        extern Flx::Random* random;

        extern Flx::SoundManager* sound;
    }
}

#endif