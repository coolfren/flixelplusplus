#ifndef PC_H
#define PC_H

#ifdef SDL_LEGACY
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#define OPENAL
#define USE_SOCKETS
#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/vorbisfile.h>
//#include "tinyxml2.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#ifdef __SWITCH__
#include <switch.h> // Switch uses the same libraries as PC, no need for a new file
#else
#define USE_CURL
#endif

#endif