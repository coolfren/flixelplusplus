#ifndef FLXSOUND_HPP
#define FLXSOUND_HPP
#include "flixel++/Common.hpp"
#include "flixel++/FlxBasic.hpp"
namespace Flx
{
    class Sound : public Basic
    {
        private:
        Mix_Chunk* internal;
        Uint32 startTime;

        OggVorbis_File vorbis;
        vorbis_info *info;

        ALuint buffer;
        ALuint source;
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