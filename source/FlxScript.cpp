#include "flixel++/FlxScript.hpp"

Flx::Script::Script()
{
}

Flx::Script::~Script()
{
}

void Flx::Script::addFunction(const char *name, std::function<void()> func)
{
}

void Flx::Script::runFunction(const char *func)
{
}

int Flx::Script::getInteger(const char *name)
{
    return 0;
}

float Flx::Script::getFloat(const char *name)
{
    return 0.0f;
}

bool Flx::Script::getBool(const char *name)
{
    return false;
}