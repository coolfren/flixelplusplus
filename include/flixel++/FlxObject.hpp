#ifndef FLXOBJECT_HPP
#define FLXOBJECT_HPP
#include "flixel++/FlxBasic.hpp"

namespace Flx
{
    class Object : public Flx::Basic
    {
        public:
        /**
         * Used for persectives on the game stage
        */
        float x = 0, y = 0, z = 0;
        float width = 0, height = 0;
               
        /// @brief Base of the engine other resources demonstrated as an invisible object
        /// @param x X position of the object
        /// @param y Y position of the object
        Object(float x, float y);
        
        ~Object();

        unsigned int vao,vbo;
    };
}
#endif