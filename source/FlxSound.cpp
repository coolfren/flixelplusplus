#include "flixel++/FlxSound.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/FlxUtils.hpp"
#include "flixel++/FlxLog.hpp"

Flx::Sound::Sound()
{
}

Flx::Sound::~Sound()
{
    #ifdef FLIXEL_OPENAL
    alDeleteSources(1, &soundData.source);
    alDeleteBuffers(1, &soundData.buffer);
    vorbis_info_clear(info);
    #endif
}

void Flx::Sound::play()
{
    startTime = Flx::Globals::game->backend->getTicks();
    #ifdef FLIXEL_OPENAL
    alSourcePlay(soundData.source);
    #endif
}

void Flx::Sound::load(const char *path)
{
    if(!Flx::Utils::fileExists(path)){
        Flx::Log::warn(path);
        return;
    }
    #if defined(TREMOR) && !defined(__WIN32)
    ov_open(fopen(path, "r"), &vorbis, nullptr, 0);
    #else
    ov_fopen(path, &vorbis);
    #endif

    info = ov_info(&vorbis, -1);

    int current_section;
    while (true)
    {
        std::vector<char> pcm(4096);
        long result = ov_read(&vorbis, pcm.data(), pcm.size(),
        #ifndef TREMOR
            0, 2, 1, 
        #endif
            &current_section
        );

        if (result == 0)
            break;

        if (result < 0)
        {
            return;
        }

        bufferData.insert(bufferData.end(), pcm.begin(), pcm.begin() + result);
    }
    soundData = Flx::Globals::sound->generateBuffers(bufferData, info->rate);
}

float Flx::Sound::getPosition()
{
    float val = 0;
    #ifdef FLIXEL_OPENAL
    alGetSourcef(soundData.buffer, AL_SEC_OFFSET, &val);
    #endif
    return val * 1000;
}
