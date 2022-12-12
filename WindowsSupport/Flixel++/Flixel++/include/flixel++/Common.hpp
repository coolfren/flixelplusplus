#ifndef COMMON_HPP
#define COMMON_HPP
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <random>
#include <cmath>
#define SDL_MAIN_HANDLED
//#define SDL_LEGACY

#ifdef SDL_LEGACY
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#endif


#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/vorbisfile.h>

#ifdef SDL_LEGACY
typedef SDL_Surface Bitmap;
#else
typedef SDL_Texture Bitmap;
#endif

#define trace(x) std::cout << '(' << __FILE__ << ',' <<  << "): " << x << std::endl

#endif