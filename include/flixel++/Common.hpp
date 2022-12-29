#ifndef COMMON_HPP
#define COMMON_HPP
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <random>
#include <cmath>
#include <memory>
#define SDL_MAIN_HANDLED
//#define SDL_LEGACY

#include "platform/platform.h"

#ifdef SDL_LEGACY
#include "flixel++/SDL_Backports.hpp"
typedef SDL_Surface Bitmap;
#else
typedef SDL_Texture Bitmap;
#endif

#ifdef TINYXML2_INCLUDED
#define TINYXML2
#endif

#endif