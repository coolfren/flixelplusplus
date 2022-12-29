#include "flixel++/FlxSound.hpp"

Flx::Sound::Sound()
{
}

Flx::Sound::~Sound()
{
    #ifdef OPENAL
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    vorbis_info_clear(info);
    #endif
}

void Flx::Sound::play()
{
    startTime = SDL_GetTicks();
    #ifdef OPENAL
    alSourcePlay(source);
    #endif
}

void Flx::Sound::load(const char *path)
{
    #if defined(TREMOR) && !defined(__WIN32)
    ov_open(fopen(path, "r"), &vorbis, nullptr, 0);
    #else
    ov_fopen(path, &vorbis);
    #endif

    info = ov_info(&vorbis, -1);

    #ifdef OPENAL
    alGenBuffers(1, &buffer);
    #endif

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
    #ifdef OPENAL
    alBufferData(buffer, AL_FORMAT_STEREO16, bufferData.data(), bufferData.size(), info->rate);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    #endif
}

float Flx::Sound::getPosition()
{
    float val = 0;
    #ifdef OPENAL
    alGetSourcef(buffer, AL_SEC_OFFSET, &val);
    #endif
    return val * 1000;
}
