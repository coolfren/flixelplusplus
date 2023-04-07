#ifndef FLXSHADER_HPP
#define FLXSHADER_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLSL(x) "#version 330\n" #x

namespace Flx
{
    namespace
    {
        static constexpr const char* _FLIXEL_DEFAULTVSHADER = GLSL(
            layout(location = 0) in vec3 vertexPos;
            layout(location = 2) in vec2 vertexCoord;

            out vec2 fragCoord;
            out vec3 Color;

            uniform mat4 projection;
            uniform mat4 model;

            void main() {
                fragCoord = vertexCoord;
                gl_Position = projection * vec4(vertexPos, 1.0f);
            }
        );

        static constexpr const char* _FLIXEL_DEFAULTFSHADER = GLSL(
            uniform sampler2D bitmap;

            out vec4 FragColor;
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

        void setShaderValue(const std::string name,glm::mat4 value);
        void setShaderValue(const std::string name,glm::vec2 value);
        void setShaderValue(const std::string name,float value);
        void setShaderValue(const std::string name,int value);

    };
}

#endif