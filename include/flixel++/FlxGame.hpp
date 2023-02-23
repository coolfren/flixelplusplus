#ifndef FLXGAME_HPP
#define FLXGAME_HPP
#include "flixel++/FlxState.hpp"
#include "flixel++/FlxManagers.hpp"
#include "flixel++/FlxBackends.hpp"
namespace Flx
{
    class Game
    {
    public:
        bool quitting = false;
        bool paused = false;

        std::string title;
        float framerate;

        Flx::State* curState;
        Flx::Backends::Backend* backend;

        Game(const char* title, int width, int height, int framerate, Flx::State* initialState, bool skipSplash);
        ~Game();
        void setupGlobals();
        void destroyGlobals();
        bool switchState(Flx::State *state);
        void runEvents();
        void run();
        void start();

        glm::mat4 perspective = glm::mat4(1.0f);

        static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
        static void glfwError(int id, const char *description)
        {
            std::cout << description << std::endl;
        }
    };
}

#endif