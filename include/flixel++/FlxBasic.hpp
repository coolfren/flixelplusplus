#ifndef FLXBASIC_HPP
#define FLXBASIC_HPP
namespace Flx
{
    /**
     * This class represents a generic flixel class which can be used to add()
    */
    class Basic
    {
        public:
        int ID;
        bool visible = false;
        Basic();
        virtual ~Basic();
        virtual void update();
        virtual void draw();
    };
}
#endif