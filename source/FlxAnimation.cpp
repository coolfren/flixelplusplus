#include "flixel++/FlxAnimation.hpp"
#include "tinyxml2.h"

Flx::Animation::Animation()
    : frames()
{}

int Flx::Animation::size()
{
    return frames.size();
}

Flx::AnimationController::AnimationController()
    : animations()
{
}

void Flx::AnimationController::fromSparrow(const char* path, const char* defaultAnim, int fps)
{
    tinyxml2::XMLDocument doc = tinyxml2::XMLDocument();
    doc.LoadFile(path);
    auto root = doc.FirstChildElement("TextureAtlas");
    tinyxml2::XMLElement* subTexture = root->FirstChildElement("SubTexture");
    do
    {
        const std::string name = std::string(subTexture->Attribute("name")).substr(0, name.length() - 4);
        if(animations.find(name) == animations.end())
            animations.insert({name, Animation()});
        const int x = subTexture->FloatAttribute("x");
        const int y = subTexture->FloatAttribute("y");
        const int width = subTexture->FloatAttribute("width");
        const int height = subTexture->FloatAttribute("height");
        const int frameX = subTexture->FloatAttribute("frameX");
        const int frameY = subTexture->FloatAttribute("frameY");

        Frame frame;
        frame.x = x;
        frame.y = y;
        frame.width = width;
        frame.height = height;
        frame.frameX = frameX;
        frame.frameY = frameY;
        animations[name].frames.push_back(frame);
        animations[name].fps = fps;
    } while((subTexture = subTexture->NextSiblingElement("SubTexture")) != nullptr);
    curAnim = &animations[defaultAnim];
    animated = true;
}

void Flx::AnimationController::play(const char* name){
    curAnim = &animations[name];
}

Flx::Frame *Flx::AnimationController::getCurAnim()
{
    return &(curAnim->frames[frameIndex]);
}