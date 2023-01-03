#include "flixel++/FlxLog.hpp"

using namespace std::literals::string_literals;

std::vector<std::string> Flx::Log::logs = std::vector<std::string>();

template<typename T>
bool Flx::Log::assert(T* type, const char* name)
{
    if(!type)
        warn("Type is null!");
    return type == nullptr;
}

void Flx::Log::warn(const char* msg)
{
    logs.push_back("Warning: "s + msg);
}

void Flx::Log::error(const char* msg)
{
    logs.push_back("Error: "s + msg);
}

const char* Flx::Log::recent(){
    try{
        return logs.at(logs.size()).c_str();
    }
    catch(std::exception& e){
        return "No recent logs";
    }
}