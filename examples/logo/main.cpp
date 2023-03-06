#include "PlayState.hpp"
#include "flixel++/FlxGame.hpp"

int main(int argc, char** argv)
{
    Flx::Game* game = new Flx::Game("Logo", 640, 480, 60.0f, new PlayState(), false);
    game->start();
    return 0;
}