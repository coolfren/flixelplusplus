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
        /// @brief Unique ID that identifies every object in the scene
        int ID;
        /// @brief Changes the object's visibility
        bool visible = false;
        /// @brief Default FlxBasic constructor
        Basic();
        
        virtual ~Basic();
        virtual void update();
        virtual void draw();
    };
}
#endif