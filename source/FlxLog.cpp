#include "flixel++/FlxLog.hpp"
#include <iostream>

template<typename T>
bool Flx::Log::assert(T* type, const char* name)
{
    bool result = type == nullptr;
    if(result)
        warn("type is null!");
    return !result;
}

void Flx::Log::warn(const char* msg)
{

}

void Flx::Log::error(const char* msg)
{

}