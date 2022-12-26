#ifndef FLXANIMATION_HPP
#define FLXANIMATION_HPP
#include "flixel++/FlxRect.hpp"

namespace Flx
{
    class Sprite;

    struct Frame : public Flx::Rect
    {
        float frameX = 0, frameY = 0;
    };

    class Animation
    {
        public:
        std::vector<Frame> frames;
        int fps = 0;
        Animation();
        int size();
    };

    class AnimationController
    {   
        public:
        Animation* curAnim;
        int frameIndex = 0;
        bool animated = false;
        std::map<const std::string, Animation> animations;
        AnimationController();
        void fromSparrow(const char* path, const char* defaultAnim, int fps);
        Frame* getCurAnim();
    };
}

#endif