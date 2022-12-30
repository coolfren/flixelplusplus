#ifndef FLIXEL_HTTP
#define FLIXEL_HTTP

#include "flixel++/Common.hpp"

#include <curl/curl.h>

namespace Flx{
    class Http{
        public:
        Http(std::string url);
        ~Http();

        CURL *curl;
        CURLcode request;

        void requestURL(std::string url);

        std::string storage;
        bool onData;
        bool onError;
    };
}


#endif