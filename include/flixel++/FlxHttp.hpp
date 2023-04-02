#ifndef FLIXEL_HTTP
#define FLIXEL_HTTP

#include "flixel++/Common.hpp"
#ifdef FLIXEL_USE_CURL
#include "curl/curl.h"

//NEED TO REWORK ON THIS

namespace Flx
{
    class Http
    {
    public:
        /// @brief Creates an new Http point
        Http(const std::string& url);
        
        ~Http();

        CURL *curl;

        std::string requestURLtext(const std::string&);

        std::string storage;
        bool onData;
        bool onError;
        bool received;

        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    };
}
#endif
#endif