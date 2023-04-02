#ifndef FLXSHADER_HPP
#define FLXSHADER_HPP

#define _FLIXEL_DEFAULTVSHADER         "#version 330\n"\
        "layout(location = 0) in vec3 vertexPos;\n"\
        "layout(location = 2) in vec2 vertexCoord;\n"\
        "out vec2 fragCoord;\n"\
        "out vec3 Color;\n"\
        "uniform mat4 projection;\n"\
        "uniform mat4 model;\n"\
        "void main() {\n"\
        "   fragCoord = vertexCoord;\n"\
        "   gl_Position = projection * vec4(vertexPos, 1.0f);\n"\
        "}\n"

        //* projection * model

#define _FLIXEL_DEFAULTFSHADER         "#version 330\n"\
        "uniform sampler2D bitmap;\n" \
        "out vec4 FragColor;\n"\
        "in vec2 fragCoord;\n"\
        "void main() {\n"\
        "   FragColor = texture(bitmap, fragCoord);\n"\
        "}\n"


#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Flx
{
    class Shader
    {
        public:
        std::string fragmentSource;
        std::string vertexSource;
        unsigned int program;
        Shader(std::string vertexShader = _FLIXEL_DEFAULTVSHADER, std::string fragmentShader = _FLIXEL_DEFAULTFSHADER);
        ~Shader();

        void setShaderValue(const std::string name,glm::mat4 value);
        void setShaderValue(const std::string name,float value);
        void setShaderValue(const std::string name,int value);

    };
}

#endif