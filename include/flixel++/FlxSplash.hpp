#ifndef FLXSPLASH_HPP
#define FLXSPLASH_HPP

#include "flixel++/FlxSprite.hpp"
#include "flixel++/FlxState.hpp"
#include "flixel++/FlxSound.hpp"
#include "flixel++/FlxText.hpp"

namespace Flx{
    class Splash : public Flx::State
    {
        public:
        Splash(Flx::State* state);
        Flx::State* nextState;

        Flx::Sprite* green;
        Flx::Sprite* blue;
        Flx::Sprite* yellow;
        Flx::Sprite* red;
        Flx::Sprite* cyan;
        Flx::Sprite* cpp;
    
        Flx::Text *flixelText;


        Flx::Sound* flixelSound;

        void create();
        void update();
    };
}


#endif