#ifndef FLXKEYBOARD_HPP
#define FLXKEYBOARD_HPP

namespace Flx
{
    class Keyboard
    {
        public:
        Keyboard();
        bool* keys;
        bool pressed(const char key);
        bool justPressed(const char key);
    };
}

#endif