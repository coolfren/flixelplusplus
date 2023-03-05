#ifndef FLXSOUND_HPP
#define FLXSOUND_HPP
#include "flixel++/Common.hpp"
#include "flixel++/FlxBasic.hpp"


namespace Flx
{
    struct SoundData
    {
        unsigned int buffer;
        unsigned int source;
    };

    // TODO: revamp Sound!
    class Sound : public Basic
    {
        public:
        uint32_t startTime;

        OggVorbis_File vorbis;
        vorbis_info* info;
        SoundData soundData;
        std::vector<char> bufferData;
        public:
        Sound();
        ~Sound();
        void play();
        void load(const char* path);
        float getPosition();
    };
}

#endif // FLXSOUND_HPP