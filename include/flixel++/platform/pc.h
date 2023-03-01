#ifndef PC_H
#define PC_H

#define FLIXEL_OPENAL
#define FLIXEL_USE_SOCKETS
#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/vorbisfile.h>
#define FLIXEL_SDL

#ifdef __SWITCH__
#include <switch.h> // Switch uses the same libraries as PC, no need for a new file
#else
#define FLIXEL_USE_CURL
#endif

#endif