#ifndef FLXGAME_HPP
#define FLXGAME_HPP
#include "flixel++/FlxState.hpp"
#include "flixel++/FlxManagers.hpp"

namespace Flx
{
    class Game
    {
        bool quitting = false;
        bool paused = false;
    public:

#ifdef SDL_LEGACY
        SDL_Surface* window;
#else
        SDL_Window* window;
        SDL_Renderer* renderer;
#endif
        float framerate;
        Flx::State* curState = nullptr;
        Game(const char* title, int width, int height, int framerate, Flx::State* initialState, bool skipSplash);
        ~Game();
        void setupGlobals();
        void destroyGlobals();
        void switchState(Flx::State* state);
        void runEvents();
        void run();
        void start();
    };
}

#endif