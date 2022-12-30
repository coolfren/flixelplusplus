#ifndef SDL_BACKPORTS_HPP
#define SDL_BACKPORTS_HPP
#include <SDL/SDL.h>

#ifdef SDL_LEGACY
#define SDL_RectEmpty(X)    ((!(X)) || ((X)->w <= 0) || ((X)->h <= 0))

bool SDL_IntersectRect(const SDL_Rect * A, const SDL_Rect * B, SDL_Rect * result);
/**
 *  This is a semi-private blit function and it performs low-level surface
 *  scaled blitting only.
 */
int
SDL_LowerBlitScaled(SDL_Surface * src, SDL_Rect * srcrect,
                SDL_Surface * dst, SDL_Rect * dstrect);

int
SDL_UpperBlitScaled(SDL_Surface * src, const SDL_Rect * srcrect,
              SDL_Surface * dst, SDL_Rect * dstrect);
#endif
#endif