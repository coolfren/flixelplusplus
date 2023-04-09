#include "flixel++/FlxAnimation.hpp"

Flx::Animation::Animation()
    : frames()
{}

int Flx::Animation::size()
{
    return frames.size();
}

Flx::AnimationController::AnimationController()
    : prefixes(), animations()
{
}

void Flx::AnimationController::fromSparrow(const char* path)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);
    auto root = doc.FirstChildElement("TextureAtlas");
    tinyxml2::XMLElement* subTexture = root->FirstChildElement("SubTexture");
    do
    {
        const std::string name = std::string(subTexture->Attribute("name")).substr(0, name.length() - 4);
        if(animations.find(name) == animations.end())
            animations.insert({name, std::vector<Flx::Frame>()});
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
        animations[name].push_back(frame);
    } while((subTexture = subTexture->NextSiblingElement("SubTexture")) != nullptr);
}

void Flx::AnimationController::play(const char* name){
    curAnim = &prefixes[name];
    animated = true;
}

void Flx::AnimationController::addByIndices(const std::string& name, const std::string& prefix, std::vector<int> indices, int fps, bool looped)
{
    prefixes.insert({name, Animation()});
    for(int i : indices)
    {
        prefixes[name].frames.push_back(&animations[prefix][i]);
    }
    prefixes[name].fps = fps;
    prefixes[name].looped = looped;
}

void Flx::AnimationController::addByPrefix(const std::string& name, const std::string& prefix, int fps, bool looped)
{
    prefixes.insert({name, Animation()});
    for(Flx::Frame& frame : animations[prefix])
    {
        prefixes[name].frames.push_back(&frame);
    }
    prefixes[name].fps = fps;
    prefixes[name].looped = looped;
}

Flx::Frame *Flx::AnimationController::getCurAnim()
{
    return (curAnim->frames[frameIndex]);
}
