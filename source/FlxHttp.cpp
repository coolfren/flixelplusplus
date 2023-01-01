#ifdef USE_CURL
#include "flixel++/FlxHttp.hpp"
#include "flixel++/FlxMacros.hpp"


Flx::Http::Http(std::string url){
    received = true;
    storage = requestURLtext(url);
}

Flx::Http::~Http()
{

}

std::string Flx::Http::requestURLtext(std::string url)
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

#endif