#include "flixel++/FlxShader.hpp"
#include "flixel++/FlxG.hpp"

Flx::Shader::Shader(std::string vertexShader, std::string fragmentShader)
    : vertexSource(vertexShader), fragmentSource(fragmentShader)
{
    Flx::Globals::game->backend->compileShader(this);
}

Flx::Shader::~Shader()
{
    delete program;
}