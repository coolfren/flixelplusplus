#ifndef FLXMANAGERS_HPP
#define FLXMANAGERS_HPP
#include "flixel++/Common.hpp"
namespace Flx
{
    class Random
    {
        private:
        std::mt19937 engine;
        public:
        Random();
        Random(int seed);
        ~Random();
        int number(int min, int max);
        float floating(float min, float max);
        bool boolean(float chance);
    };
    
    class SoundManager
    {
        private:
        #ifdef OPENAL
        ALCdevice *device;
        ALCcontext *context;
        #endif
        public:
        SoundManager();
        ~SoundManager();
    };
}

#endif // FLXMANAGERS_HPP