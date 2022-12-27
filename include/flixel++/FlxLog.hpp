#ifndef FLXLOG_HPP
#define FLXLOG_HPP

namespace Flx
{
    class Log
    {
        template<typename T>
        static bool assert(T* type, const char* name);
        static void warn(const char* msg);
        static void error(const char* msg);     
    };
}
#endif