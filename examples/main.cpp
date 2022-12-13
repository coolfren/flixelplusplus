#include "State.hpp"
#include "flixel++/FlxGame.hpp"

int main(int argc, char** argv)
{
    Flx::Game* game = new Flx::Game("Flixel++", 640, 480, 60.0f, new PlayState());
    game->start();
    return 0;
}