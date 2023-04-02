#include "State.hpp"
#include "flixel++/FlxGame.hpp"

int main(int argc, char** argv)
{
    Flx::Game* game = new Flx::Game("Better Use Flixel++!", 1920, 1080, 60.0f, new PlayState(), true);
    game->start();
    return 0;
}
