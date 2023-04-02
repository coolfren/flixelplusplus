#ifndef FLXKEYBOARD_HPP
#define FLXKEYBOARD_HPP

namespace Flx
{
    class Keyboard
    {
        public:
        Keyboard();
        bool* keys;
        bool pressed(const unsigned char key);
        bool justPressed(const unsigned char key);
    };
}

#endif