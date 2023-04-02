#ifndef FLXSTATE_HPP
#define FLXSTATE_HPP
#include <flixel++/Common.hpp>
#include <flixel++/FlxBasic.hpp>
#include <flixel++/FlxGroup.hpp>

namespace Flx
{
    /**
     * The State class which is used to define what happens in a state.
     * this class should be extended to make your own states.
     * @note If you're overriding update or draw, make sure to call Flx::State::update() or Flx::State::draw() somewhere in the function!
    */
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