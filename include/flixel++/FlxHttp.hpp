#ifndef FLIXEL_HTTP
#define FLIXEL_HTTP

#include "flixel++/Common.hpp"

namespace Flx
{
    class Http
    {
    public:
        Http(std::string url);
        ~Http();

        CURL *curl;

        std::string requestURLtext(std::string url);

        std::string storage;
        bool onData;
        bool onError;
        bool received;

        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
        {
            ((std::string *)userp)->append((char *)contents, size * nmemb);
            return size * nmemb;
        }
    };
}

#endif