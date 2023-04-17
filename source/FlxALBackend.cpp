#include "flixel++/FlxAudioBackends.hpp"

using Flx::Backends::OpenAL;

OpenAL::OpenAL()
{
    device = alcOpenDevice(NULL);
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
}

OpenAL::~OpenAL()
{
    alcDestroyContext (context);
    alcCloseDevice (device);
}

Flx::SoundData OpenAL::generateBuffers(std::vector<char>& bufferData, size_t rate)
{
    ALuint buffer, source;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_STEREO16, bufferData.data(), bufferData.size(), rate);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    return SoundData{buffer, source};
}

void OpenAL::play(Flx::SoundData& soundData)
{
    alSourcePlay(soundData.source);
}

void OpenAL::pause(Flx::SoundData& soundData)
{
    alSourcePause(soundData.source);
}

void OpenAL::stop(Flx::SoundData& soundData)
{
    alSourceStop(soundData.source);
}

void OpenAL::destroyAudio(Flx::SoundData& soundData)
{
    alDeleteSources(1, &soundData.source);
    alDeleteBuffers(1, &soundData.buffer);
}

float OpenAL::currentPosition(Flx::SoundData& soundData)
{
    float val = 0;
    alGetSourcef(soundData.buffer, AL_SEC_OFFSET, &val);
    return val * 1000;
}