#ifndef FLXAUDIOBACKENDS_HPP
#define FLXAUDIOBACKENDS_HPP
#include "flixel++/FlxSound.hpp"

namespace Flx::Backends
{
    class AudioBackend
    {
        public:
        virtual ~AudioBackend(){};
        virtual Flx::SoundData generateBuffers(std::vector<char>& bufferData, size_t rate) = 0;
        virtual void play(Flx::SoundData& soundData) = 0;
        virtual void pause(Flx::SoundData& soundData) = 0;
        virtual void stop(Flx::SoundData& soundData) = 0;
        virtual void destroyAudio(Flx::SoundData& soundData) = 0;
        virtual float currentPosition(Flx::SoundData& soundData) = 0;
    };

    class OpenAL : public AudioBackend
    {
        ALCdevice *device;
        ALCcontext *context;
        public:
        OpenAL();
        ~OpenAL();
        Flx::SoundData generateBuffers(std::vector<char>& bufferData, size_t rate);
        void play(Flx::SoundData& soundData);
        void pause(Flx::SoundData& soundData);
        void stop(Flx::SoundData& soundData);
        void destroyAudio(Flx::SoundData& soundData);
        float currentPosition(Flx::SoundData& soundData);
    };
}

#endif