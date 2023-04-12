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
        std::vector<Frame*> frames;
        int fps = 0;
        bool looped = true;
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
        std::map<const std::string, Animation> prefixes;
        std::map<const std::string, std::vector<Flx::Frame>> animations;
        AnimationController();
        void fromSparrow(const char* path);

        void addByIndices(const std::string& name, const std::string& prefix, std::vector<int> indices, int fps = 30, bool looped = true);
        void addByPrefix(const std::string& name, const std::string& prefix, int fps = 30, bool looped = true);

        void play(const char* name);
        Frame* getCurAnim();
    };
}

#endif