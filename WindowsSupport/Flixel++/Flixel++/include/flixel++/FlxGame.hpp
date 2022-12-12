#ifndef FLXGAME_HPP
#define FLXGAME_HPP
#include "flixel++/FlxState.hpp"
#include "flixel++/FlxManagers.hpp"

namespace Flx
{
    class Game
    {
        public:
        
        #ifdef SDL_LEGACY
        SDL_Surface* window;
        #else
        SDL_Window* window;
        SDL_Renderer* renderer;
        #endif
        int framerate;
        Flx::State* curState = nullptr;
        Game(const char* title, int width, int height, int framerate, Flx::State* initialState);
        ~Game();
        void setupGlobals();
        void destroyGlobals();
        void switchState(Flx::State* state);
        void run();
        void start();
    };

    namespace Globals
    {
        extern Flx::Game* _curGame;

        extern Flx::Random* random;

        extern Flx::SoundManager* sound;
    }
}

#endif