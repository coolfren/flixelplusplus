#include "flixel++/FlxGame.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxAssets.hpp"
#include "flixel++/FlxMacros.hpp"
#include "flixel++/FlxSplash.hpp"

int Flx::Globals::width = 0;
int Flx::Globals::height = 0;

Flx::Game *Flx::Globals::game = nullptr;
Flx::Random *Flx::Globals::random = nullptr;
Flx::SoundManager *Flx::Globals::sound = nullptr;
Flx::Keyboard *Flx::Globals::keys = nullptr;
Flx::Mouse *Flx::Globals::mouse = nullptr;

bool Flx::Globals::switchState(Flx::State *state)
{
    return game->switchState(state);
}

Flx::Game::Game(const char *title, int width, int height, int framerate, Flx::State *initialState, bool skipSplash)
    : framerate(framerate)
{
#if defined(__SWITCH__)
    consoleInit(NULL);
    romfsInit();
#elif defined(__3DS__)
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    romfsInit();
#endif

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef SDL_LEGACY
    window = SDL_SetVideoMode(width, height, 0, 0);
    SDL_WM_SetCaption(title, NULL);
    SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 0));
#else
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to load the gl Window!" << std::endl;
        glfwSetErrorCallback(&glfwError);
        glfwInit();
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#endif
    setupGlobals();
    SDL_ShowCursor(0);

    Flx::Globals::width = width;
    Flx::Globals::height = height;

    Flx::Globals::mouse = new Flx::Mouse();
    if (skipSplash)
        switchState(initialState);
    else
        switchState(new Flx::Splash(initialState));
}

Flx::Game::~Game()
{
    destroyGlobals();

#ifdef SDL_LEGACY
    SDL_FreeSurface(window);
#else
    glfwTerminate();
#endif
    TTF_Quit();
    SDL_Quit();
}

void Flx::Game::setupGlobals()
{
    Flx::Globals::game = this;

    Flx::Globals::random = new Flx::Random();

    Flx::Globals::sound = new Flx::SoundManager();

    Flx::Globals::keys = new Flx::Keyboard();

    Flx::Assets::initialize();

    Flx::Globals::mouse = new Flx::Mouse();
}

void Flx::Game::destroyGlobals()
{
    delete Flx::Globals::random;
    delete Flx::Globals::sound;
    delete Flx::Globals::keys;
    delete Flx::Globals::mouse;
}

bool Flx::Game::switchState(Flx::State *state)
{
    if (curState != nullptr)
    {
        delete curState;
    }
    curState = state;
    curState->create();
    return true;
}

void Flx::Game::runEvents()
{
    /*SDL_Event e;
    while (!glfwWindowShouldClose(window))
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
#ifndef SDL_LEGACY
            if (e.key.repeat == 0)
#endif
                Flx::Globals::keys->keys[e.key.keysym.sym % 255] = true;
            break;
        case SDL_KEYUP:
            Flx::Globals::keys->keys[e.key.keysym.sym % 255] = false;
            break;
#ifndef SDL_LEGACY
        case SDL_WINDOWEVENT:
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
                // SDL_GetWindowSize(window, &Flx::Globals::width, &Flx::Globals::height);
                curState->onResize(Flx::Globals::width, Flx::Globals::height);
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                paused = false;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                paused = true;
                break;
            }
            break;
#endif
        case SDL_QUIT:
            quitting = true;
            break;
        default:
            break;
        }
    }*/
}

void Flx::Game::run()
{
    Flx::Globals::mouse->update();
#ifdef SDL_LEGACY
    curState->update();
    SDL_FillRect(window, NULL, 0x000000);
    curState->draw();
    Flx::Globals::mouse->draw();
    SDL_Flip(window);
#else
    curState->update();
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //SDL_RenderClear(renderer);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    curState->draw();
    Flx::Globals::mouse->draw();
   //SDL_RenderPresent(renderer);
#endif
}

void Flx::Game::start()
{
    /*while (!quitting)
    {
        runEvents();
        if (!paused)
            run();
        SDL_Delay(1000.0f / framerate);
    }*/
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, true);
        }

        runEvents();
        if (!paused)
            run();

        // Swap the buffers
        glfwSwapBuffers(window);
        // Processes the window
        glfwPollEvents();
    }
}

void Flx::Game::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}