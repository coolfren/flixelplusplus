#include "flixel++/FlxShader.hpp"
#include "flixel++/FlxG.hpp"
#include "flixel++/Common.hpp"
#include <GL/glew.h>

Flx::Shader::Shader(std::string vertexShader, std::string fragmentShader)
    : vertexSource(vertexShader), fragmentSource(fragmentShader)
{
    Flx::Globals::game->backend->compileShader(this);
}

Flx::Shader::~Shader()
{
}

void Flx::Shader::setShaderValue(const std::string& name, glm::mat4 value){
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Flx::Shader::setShaderValue(const std::string& name, glm::vec2 value){
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Flx::Shader::setShaderValue(const std::string& name, float value){
	glUniform1f(glGetUniformLocation(program, name.c_str()),value);
}

void Flx::Shader::setShaderValue(const std::string& name, int value){
	glUniform1i(glGetUniformLocation(program, name.c_str()),value);
}