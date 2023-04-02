#include "State.hpp"
#include "flixel++/FlxGame.hpp"

int main(int argc, char** argv)
{
    Flx::Game* game = new Flx::Game("Flixel++", 1920, 1080, 60.0f, new PlayState(), false);
    game->start();
    return 0;
}
