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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

#ifdef SDL_LEGACY
    window = SDL_SetVideoMode(width, height, 0, 0);
    SDL_WM_SetCaption(title, NULL);
    SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 0));
#else
    window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Failed to load the sdl/gl Window!" << std::endl;
        SDL_GetError();
    }
    GLenum verifyGlew = glewInit();
    if (verifyGlew != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(verifyGlew));
    }

    glContext = SDL_GL_CreateContext(window);
    if(glContext != nullptr){
        std::cout << "Failed to create a GL context" << std::endl;
        SDL_GetError();
    }

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
    SDL_Event e;
    while (SDL_PollEvent(&e))
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
    }
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
    glClearColor(1.0f,0.5f,0.35f,1.0f);

    perspective = glm::ortho(0.0f, (float)Flx::Globals::width, (float)Flx::Globals::height, 0.0f, -1.0f, 1.0f);

    curState->update();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    curState->draw();
    Flx::Globals::mouse->draw();
    // SDL_RenderPresent(renderer);
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
    while (!quitting)
    {
        runEvents();
        if (!paused)
            run();

        SDL_GL_SwapWindow(window);
    }
}

void Flx::Game::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}