#ifndef FLXSTATE_HPP
#define FLXSTATE_HPP
#include <flixel++/Common.hpp>
#include <flixel++/FlxBasic.hpp>
#include <flixel++/FlxGroup.hpp>

namespace Flx
{
    class State : public Flx::Group
    {
        public:
        //Flx::SubState substate;
        State();
        virtual void create();
        virtual void update();
        virtual void onResize(int width, int height);
        void draw();
    };
    class SubState : public Flx::State
    {
        public:
        SubState();
        ~SubState();
        void update();
        void draw();
    };
}
#endif