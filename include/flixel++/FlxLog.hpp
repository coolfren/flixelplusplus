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

        static void warn(const std::string& msg);
        static void error(const std::string& msg);
        static const char* recent();
    };
}
#endif