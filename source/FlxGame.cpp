#include "flixel++/FlxGame.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxAssets.hpp"
#include "flixel++/FlxMacros.hpp"
#include "flixel++/FlxSplash.hpp"

int Flx::Globals::width = 0;
int Flx::Globals::height = 0;

Flx::Game* Flx::Globals::game = nullptr;
Flx::Random* Flx::Globals::random = nullptr;
Flx::SoundManager* Flx::Globals::sound = nullptr;
Flx::Keyboard* Flx::Globals::keys = nullptr;
Flx::Mouse* Flx::Globals::mouse = nullptr;

bool Flx::Globals::switchState(Flx::State* state){
    return game->switchState(state);
}

void initializeConsoles()
{
    #if defined(__3DS__) || defined(__SWITCH__)
    romfsInit();
    #endif
}

Flx::Game::Game(const char* title, int width, int height, int framerate, Flx::State* initialState, bool skipSplash)
    : title(),
    framerate(framerate),
    curState(nullptr),
    backend(nullptr)
{
    this->title = title;

    Flx::Globals::game = this;

    Flx::Globals::width = width;
    Flx::Globals::height = height;

    this->backend = new Flx::Backends::SDL();

    initializeConsoles();

    setupGlobals();

    if(skipSplash)
        switchState(initialState);
    else
        switchState(new Flx::Splash(initialState));
}

Flx::Game::~Game()
{
    destroyGlobals();
    delete backend;
}

void Flx::Game::setupGlobals()
{
    Flx::Globals::random = new Flx::Random();

    Flx::Globals::sound = new Flx::SoundManager();

    Flx::Globals::keys = new Flx::Keyboard();

    Flx::Globals::mouse = new Flx::Mouse();
}

void Flx::Game::destroyGlobals()
{
    delete Flx::Globals::random;
    delete Flx::Globals::sound;
    delete Flx::Globals::keys;
    delete Flx::Globals::mouse;
}

bool Flx::Game::switchState(Flx::State* state)
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
    backend->runEvents();
}

void Flx::Game::run()
{
    backend->update();
}

void Flx::Game::start()
{
    while (!quitting)
    {
        runEvents();
        if(!paused)
            run();
        backend->delay(1000.0f / framerate);
    }
}