#ifndef FLXTEXT_HPP
#define FLXTEXT_HPP

#include "flixel++/FlxSprite.hpp"

namespace Flx
{
    class Text : public Flx::Sprite
    {
        public:
        std::string text;
        Text(float x, float y, const std::string& text);
        ~Text();

        void setText(std::string newText);
        void drawText();

        // TODO: FlxFont
        void* font;
    };
}

#endif