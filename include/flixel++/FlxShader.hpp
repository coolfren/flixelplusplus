#ifndef FLXSHADER_HPP
#define FLXSHADER_HPP

#define _FLIXEL_DEFAULTVSHADER "#version 330 core\n" \
"layout (location = 0) in vec3 position;\n" \
"void main(){\n" \
"glPosition = vec4(position.x, position.y, position.z, 1.0);\n" \
"}\n"

#define _FLIXEL_DEFAULTFSHADER "version 330 core\n" \
"out vec4 FragColor;\n" \
"void main(){\n" \
"FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n" \
"}\n"

#include <iostream>

namespace Flx
{
    class Shader
    {
        public:
        std::string fragmentSource;
        std::string vertexSource;
        void* program;
        Shader(std::string vertexShader = _FLIXEL_DEFAULTVSHADER, std::string fragmentShader = _FLIXEL_DEFAULTFSHADER);
        ~Shader();
    };
}

#endif