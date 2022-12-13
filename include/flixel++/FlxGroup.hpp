#ifndef FLXGROUP_HPP
#define FLXGROUP_HPP
#include <flixel++/Common.hpp>
#include <flixel++/FlxBasic.hpp>

namespace Flx
{
    class Group : public Flx::Basic
    {
        public:
        std::vector<Flx::Basic*> members;
        Group();
        ~Group();
        Flx::Basic* operator+=(Flx::Basic& obj);
        Flx::Basic* operator+=(Flx::Basic* obj);
        Flx::Basic* add(Flx::Basic& obj);
        Flx::Basic* add(Flx::Basic* obj);
        virtual void update();
        void draw();
    };
}
#endif