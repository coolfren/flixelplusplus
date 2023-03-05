#ifndef FLXANIMATION_HPP
#define FLXANIMATION_HPP
#include "flixel++/FlxRect.hpp"

namespace Flx
{
    class Sprite;

    /**
     * The basic frame class used for animation.
     * @extends Flx::Rect
    */
    struct Frame : public Flx::Rect
    {
        float frameX = 0, frameY = 0;
    };

    /**
     * Animation class which contains the frames for that animation.
    */
    class Animation
    {
        public:
        std::vector<Frame> frames;
        int fps = 0;
        Animation();
        int size();
    };

    /**
     * The animation controller that is used internally.
    */
    class AnimationController
    {   
        public:
        Animation* curAnim;
        int frameIndex = 0;
        bool animated = false;
        std::map<const std::string, Animation> animations;
        AnimationController();
        void fromSparrow(const char* path, const char* defaultAnim, int fps);
        void play(const char* name);
        Frame* getCurAnim();
    };
}

#endif