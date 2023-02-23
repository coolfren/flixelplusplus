#include "flixel++/Common.hpp"
#ifdef FLIXEL_USE_CURL
#include "flixel++/FlxHttp.hpp"
#include "flixel++/FlxMacros.hpp"
#include "curl/curl.h"

Flx::Http::Http(const std::string& url){
    received = true;
    storage = requestURLtext(url);
}

Flx::Http::~Http()
{

}

std::string Flx::Http::requestURLtext(const std::string& url)
{   
    std::string result;
    CURLcode exit;

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

    exit = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if(exit == CURLE_OK){
        onData = true;
        onError = false;
        received = false;
    }
    else{
        onError = true;
        onData = false;
    }


    return result;
}

size_t Flx::Http::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

#endif