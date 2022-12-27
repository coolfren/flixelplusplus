#include "flixel++/FlxGame.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxAssets.hpp"
#include "flixel++/FlxMacros.hpp"

float Flx::Globals::width = 0;
float Flx::Globals::height = 0;

Flx::Game* Flx::Globals::_curGame = nullptr;
Flx::Random* Flx::Globals::random = nullptr;
Flx::SoundManager* Flx::Globals::sound = nullptr;
Flx::Keyboard* Flx::Globals::keys = nullptr;

Flx::Game::Game(const char* title, int width, int height, int framerate, Flx::State* initialState)
    : framerate(framerate)
{
#ifdef __SWITCH__
    consoleInit(NULL);
    romfsInit();
#endif
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
#ifdef SDL_LEGACY
    window = SDL_SetVideoMode(width, height, 0, 0);
    SDL_WM_SetCaption(title, NULL);
    SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 0));
#else
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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
    TTF_Quit();
    SDL_Quit();
}

void Flx::Game::setupGlobals()
{
    Flx::Globals::_curGame = this;

    Flx::Globals::random = new Flx::Random();

    Flx::Globals::sound = new Flx::SoundManager();

    Flx::Globals::keys = new Flx::Keyboard();

    Flx::Assets::initialize();
}

void Flx::Game::destroyGlobals()
{
    delete Flx::Globals::random;
    delete Flx::Globals::sound;
}

void Flx::Game::switchState(Flx::State* state)
{

    if (curState != nullptr)
    {
        delete curState;
    }
    curState = state;
    curState->create();
}

void Flx::Game::runEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        switch(e.type)
        {
            case SDL_KEYDOWN:
                Flx::Globals::keys->keys[e.key.keysym.sym % 255] = true;
                break;
            case SDL_KEYUP:
                Flx::Globals::keys->keys[e.key.keysym.sym % 255] = false;
                break;
            case SDL_WINDOWEVENT:
                switch(e.window.event){
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        paused = false;
                            break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        paused = true;
                        break;
                }
                break;
            case SDL_QUIT:
                quitting = true;
                break;
            default:
                break;
        }
    }
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
    while (!quitting)
    {
        runEvents();
        if(!paused)
            run();
        SDL_Delay(1000.0f / framerate);
    }
}