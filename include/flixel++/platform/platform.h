#ifndef PLATFORM_H
#define PLATFORM_H

#if (__3DS__)
#include "3ds.h"
#elif (__WII__)
#include "wii.h"
#else
#include "pc.h"
#endif

#endif