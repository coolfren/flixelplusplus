#include "flixel++/FlxSound.hpp"

Flx::Sound::Sound()
{
}

Flx::Sound::~Sound()
{
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    vorbis_info_clear(info);
}

void Flx::Sound::play()
{
    startTime = SDL_GetTicks();
    alSourcePlay(source);
}

void Flx::Sound::load(const char *path)
{
    ov_fopen(path, &vorbis);
    info = ov_info(&vorbis, -1);
    alGenBuffers(1, &buffer);
    int current_section;
    while (true)
    {
        std::vector<char> pcm(4096);
        long result = ov_read(&vorbis, pcm.data(), pcm.size(), 0, 2, 1, &current_section);

        if (result == 0)
            break;

        if (result < 0)
        {
            return;
        }

        bufferData.insert(bufferData.end(), pcm.begin(), pcm.begin() + result);
    }
    alBufferData(buffer, AL_FORMAT_STEREO16, bufferData.data(), bufferData.size(), info->rate);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
}

float Flx::Sound::getPosition()
{
    float val = 0;
    alGetSourcef(buffer, AL_SEC_OFFSET, &val);
    return val * 1000;
}
