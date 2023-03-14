#ifndef FLXSHADER_HPP
#define FLXSHADER_HPP

#define GLSL(x) "#version 330\n" #x
#define HLSL(x) "#pragma target 5.0\n" #x
#include <iostream>

namespace Flx
{
    namespace
    {
        static constexpr const char* _FLIXEL_DEFAULTVSHADER = GLSL(
            layout(location = 0) in vec3 vertexPos;
            layout(location = 1) in vec3 vertexColor;
            layout(location = 2) in vec2 vertexCoord;

            out vec2 fragCoord;
            out vec3 Color;

            uniform mat4 transform;

            void main() {
                Color = vertexColor;
                gl_Position = transform * vec4(vertexPos, 1.0);
                fragCoord = vec2(vertexCoord.x, -vertexCoord.y);
            }
        );

        static constexpr const char* _FLIXEL_DEFAULTFSHADER = GLSL(
            uniform sampler2D bitmap;

            out vec4 FragColor;

            in vec3 Color;
            in vec2 fragCoord;

            void main() {
                FragColor = texture(bitmap, fragCoord);
            }
        );
    }
    
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