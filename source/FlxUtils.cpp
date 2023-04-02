#include "flixel++/FlxUtils.hpp"
#include <fstream>
bool Flx::Utils::fileExists(const char* path)
{
    if(FILE *file = fopen(path, "r"))
    {
        fclose(file);
        return true;
    }
    return false;
}