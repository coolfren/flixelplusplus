#include "State.hpp"
#include "flixel++/FlxGame.hpp"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

int main(int argc, char** argv)
{
    Flx::Game* game = new Flx::Game("Flixel++", 1920, 1080, 60.0f, new PlayState(), false);
    game->start();
    
    unsigned int VAO,VBO[2];
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    return 0;
}
