#include "flixel++/FlxHttp.hpp"
#include <curl/curl.h>


Flx::Http::Http(std::string url){
    requestURL(url);
}

Flx::Http::~Http()
{

}

void Flx::Http::requestURL(std::string url)
{
    curl = curl_easy_init();

    curl_easy_setopt(curl,CURLOPT_URL,url.c_str());

    request = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if(request == CURLE_OK){
        storage = std::to_string(request);
        storage.pop_back();

        onData = true;
        onError = false;
    }
    else{
        onError = true;
        onData = false;
    }

}

