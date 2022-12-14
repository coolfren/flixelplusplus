#include "flixel++/FlxGame.hpp"

float Flx::Globals::width = 0;
float Flx::Globals::height = 0;

Flx::Game *Flx::Globals::_curGame = nullptr;
Flx::Random *Flx::Globals::random = nullptr;
Flx::SoundManager *Flx::Globals::sound = nullptr;

Flx::Game::Game(const char *title, int width, int height, int framerate, Flx::State *initialState)
    : framerate(framerate)
{
    #ifdef __SWITCH__
    consoleInit(NULL);
    romfsInit();
    #endif
    SDL_Init(SDL_INIT_EVERYTHING);
#ifdef SDL_LEGACY
    window = SDL_SetVideoMode(width, height, 0, 0);
    SDL_WM_SetCaption(title, NULL);
    SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 0));
#else
    test = { 1,1,1,1 };
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderFillRect(renderer, &test);
    test.w = 1;
#endif

    setupGlobals();

    Flx::Globals::width = width;
    Flx::Globals::height = height;

    switchState(initialState);
}

Flx::Game::~Game()
{
    destroyGlobals();

#ifdef SDL_LEGACY
    SDL_FreeSurface(window);
#else
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
#endif
    SDL_Quit();
}

void Flx::Game::setupGlobals()
{
    Flx::Globals::_curGame = this;

    Flx::Globals::random = new Flx::Random();

    Flx::Globals::sound = new Flx::SoundManager();
}

void Flx::Game::destroyGlobals()
{
    delete Flx::Globals::random;
    delete Flx::Globals::sound;
}

void Flx::Game::switchState(Flx::State *state)
{

    if (curState != nullptr)
    {
        delete curState;
    }
    curState = state;
    curState->create();
}

void Flx::Game::run()
{
#ifdef SDL_LEGACY
    curState->update();
    SDL_Flip(window);
    curState->draw();
#else
    curState->update();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    curState->draw();
    SDL_RenderPresent(renderer);
#endif
}

void Flx::Game::start()
{
    bool quitting = false;
    SDL_Event e;
    while (!quitting)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quitting = true;
            }
        }
        run();
        SDL_Delay(1000.0f / framerate);
    }
}