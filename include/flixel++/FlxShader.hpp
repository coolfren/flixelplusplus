#ifndef FLXSHADER_HPP
#define FLXSHADER_HPP

#define _FLIXEL_DEFAULTVSHADER         "#version 330\n"\
        "layout(location = 0) in vec3 vertexPos;\n"\
        "layout(location = 1) in vec3 vertexColor;\n"\
        "layout(location = 2) in vec2 vertexCoord;\n"\
        "out vec2 fragCoord;\n"\
        "out vec3 Color;\n"\
        "void main() {\n"\
        "   fragCoord = vertexCoord;\n"\
        "   Color = vertexColor;\n"\
        "   gl_Position = vec4(vertexPos, 1.0);\n"\
        "}\n"

#define _FLIXEL_DEFAULTFSHADER         "#version 330\n"\
        "uniform sampler2D bitmap;\n" \
        "out vec4 FragColor;\n"\
        "in vec3 Color;\n"\
        "in vec2 fragCoord;\n"\
        "void main() {\n"\
        "   FragColor = texture(bitmap, fragCoord);\n"\
        "}\n"

#include <iostream>

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
    };
}

#endif