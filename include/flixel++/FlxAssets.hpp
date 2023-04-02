#ifndef FLXASSETS_HPP
#define FLXASSETS_HPP
namespace Flx
{
    namespace Assets
    {
        /// @brief Default engine's font (can be overwritten in every FlxText)
        extern void* defaultFont;
        /// @brief Default engine's cursor bitmap (can be overwritten in the game class FlxMouse)
        extern void* defaultCursor;
    }
}

#endif