#ifndef FLXSCRIPT_HPP
#define FLXSCRIPT_HPP
#include <map>
#include <functional>

namespace Flx
{

    class Script
    {
        private:
        void* interp;
        public:
        Script();
        ~Script();
        void addFunction(const char* name, std::function<void()> func);
        void runFunction(const char* func);
        int getInteger(const char* name);
        float getFloat(const char* name);
        bool getBool(const char* name);
    };
}

#endif