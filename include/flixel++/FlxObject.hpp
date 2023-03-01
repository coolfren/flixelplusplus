#ifndef FLXOBJECT_HPP
#define FLXOBJECT_HPP
#include "flixel++/FlxBasic.hpp"

namespace Flx
{
    class Object : public Flx::Basic
    {
        public:
        float x = 0, y = 0;
        float width = 0, height = 0;
        
        Object(float x, float y);
        ~Object();

        unsigned int vao,vbo;
    };
}
#endif