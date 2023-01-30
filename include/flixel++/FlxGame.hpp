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
        GLFWwindow* window;
#endif
        float framerate;
        Flx::State* curState = nullptr;
        Game(const char* title, int width, int height, int framerate, Flx::State* initialState, bool skipSplash = false);
        ~Game();
        void setupGlobals();
        void destroyGlobals();
        bool switchState(Flx::State* state);
        void runEvents();
        void run();
        void start();


        static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
        static void glfwError(int id, const char* description)
        {
            std::cout << description << std::endl;
        }
    };
}

#endif