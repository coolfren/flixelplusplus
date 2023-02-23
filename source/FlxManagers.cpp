#include "flixel++/FlxManagers.hpp"

Flx::Random::Random()
    : engine(std::chrono::system_clock::now().time_since_epoch().count())
{
}

Flx::Random::~Random() {}

Flx::Random::Random(int seed)
    : engine(seed)
{
}

int Flx::Random::number(int min, int max)
{
    return engine() % (max - min + 1) + min;
}

float Flx::Random::floating(float min, float max)
{
    return static_cast<float>(engine()) / engine.max() * (max - min) + min;
}

bool Flx::Random::boolean(float chance)
{
    return floating(0.0f, 100.0f) < chance;
}

Flx::SoundManager::SoundManager()
    : music(nullptr)
{
    #ifdef FLIXEL_OPENAL
    device = alcOpenDevice(NULL);
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    #endif
}

Flx::SoundManager::~SoundManager()
{
    #ifdef FLIXEL_OPENAL
    alcDestroyContext (context);
    alcCloseDevice (device);
    #endif
}