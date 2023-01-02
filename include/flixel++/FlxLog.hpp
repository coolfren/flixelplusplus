#ifndef FLXLOG_HPP
#define FLXLOG_HPP
#include <vector>
#include <string>
namespace Flx
{
    class Log
    {
        public:
        static std::vector<std::string> logs;

        template<typename T>
        static bool assert(T* type, const char* name);
        static void warn(const char* msg);
        static void error(const char* msg);
        static const char* recent();
    };
}
#endif