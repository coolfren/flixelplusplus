#ifndef FLXBASIC_HPP
#define FLXBASIC_HPP
namespace Flx
{
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