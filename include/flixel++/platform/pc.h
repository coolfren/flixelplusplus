#ifndef PC_H
#define PC_H

#define FLIXEL_OPENAL
#define FLIXEL_USE_SOCKETS
#define FLIXEL_SDL
#define FLIXEL_OPENGL

#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/vorbisfile.h>

#ifdef __SWITCH__
#include <switch.h> // Switch uses the same libraries as PC, no need for a new file
#else
#define FLIXEL_USE_CURL
#endif

#endif