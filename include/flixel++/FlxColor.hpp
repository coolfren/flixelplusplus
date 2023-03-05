#ifndef FLXCOLOR_HPP
#define FLXCOLOR_HPP
#include "flixel++/Common.hpp"

namespace Flx
{
    struct Color
    {
        /// @brief Red color value
        uint8_t r;
        /// @brief Green color value
        uint8_t g;
        /// @brief Blue color value
        uint8_t b; 
        /// @brief Alpha color value
        uint8_t a;

        /** 
         * @brief Used to create an specific color for any sprite in the engine
         * @param red Red Value
         * @param green Green Value
         * @param blue Blue Value
         * @param alpha Alpha Value
         **/
        Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

        /** 
         * @brief Creates a color from an given hex value
         * @param color Hex value (Ex: #FFFFFF or 0xFF0FFF)
         * @return An Color struct
         **/
        static Color fromHex(int color);
    };
}

#endif