#ifndef FLXLOG_HPP
#define FLXLOG_HPP
namespace Flx
{
    class Log
    {
        static void warn(const char* msg);
        static void error(const char* msg);     
    };
}
#endif