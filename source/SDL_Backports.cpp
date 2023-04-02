#include "flixel++/SDL_Backports.hpp"

#ifdef SDL_LEGACY
int
SDL_LowerBlitScaled(SDL_Surface * src, SDL_Rect * srcrect,
                SDL_Surface * dst, SDL_Rect * dstrect)
{

    /* Save off the original dst width, height */
    int dstW = dstrect->w;
    int dstH = dstrect->h;
    SDL_Rect full_rect;
    SDL_Rect final_dst = *dstrect;
    SDL_Rect final_src = *srcrect;

    /* Clip the dst surface to the dstrect */
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = dst->w;
    full_rect.h = dst->h;
    if (!SDL_IntersectRect(&final_dst, &full_rect, &final_dst)) {
        return 0;
    }

    /* Did the dst width change? */
    if ( dstW != final_dst.w ) {
        /* scale the src width appropriately */
        final_src.w = final_src.w * dst->clip_rect.w / dstW;
    }

    /* Did the dst height change? */
    if ( dstH != final_dst.h ) {
        /* scale the src width appropriately */
        final_src.h = final_src.h * dst->clip_rect.h / dstH;
    }

    /* Clip the src surface to the srcrect */
    full_rect.x = 0;
    full_rect.y = 0;
    full_rect.w = src->w;
    full_rect.h = src->h;
    if (!SDL_IntersectRect(&final_src, &full_rect, &final_src)) {
        return 0;
    }
    if ( !(src->map) && src->format == dst->format )  {
        return SDL_SoftStretch( src, &final_src, dst, &final_dst );
    } else {
        return SDL_LowerBlit( src, &final_src, dst, &final_dst );
    }
}
bool SDL_IntersectRect(const SDL_Rect * A, const SDL_Rect * B, SDL_Rect * result)
{
    int Amin, Amax, Bmin, Bmax;

    if (!A || !B || !result) {
        // TODO error message
        return SDL_FALSE;
    }

    /* Special cases for empty rects */
    if (SDL_RectEmpty(A) || SDL_RectEmpty(B)) {
        return SDL_FALSE;
    }
    
    /* Horizontal intersection */
    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    if (Bmin > Amin)
        Amin = Bmin;
    result->x = Amin;
    if (Bmax < Amax)
        Amax = Bmax;
    result->w = Amax - Amin;

    /* Vertical intersection */
    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    if (Bmin > Amin)
        Amin = Bmin;
    result->y = Amin;
    if (Bmax < Amax)
        Amax = Bmax;
    result->h = Amax - Amin;

    return !SDL_RectEmpty(result);
}

int
SDL_UpperBlitScaled(SDL_Surface * src, const SDL_Rect * srcrect,
              SDL_Surface * dst, SDL_Rect * dstrect)
{
    SDL_Rect final_src, final_dst, fulldst;

    /* Make sure the surfaces aren't locked */
    if (!src || !dst) {
    }
    if (src->locked || dst->locked) {
    }

    /* If the destination rectangle is NULL, use the entire dest surface */
    if (dstrect == NULL) {
        fulldst.x = fulldst.y = 0;
        dstrect = &fulldst;
    }

    /* clip the source rectangle to the source surface */
    if (srcrect) {
        int maxw, maxh;

        final_src.x = srcrect->x;
        final_src.w = srcrect->w;
        if (final_src.x < 0) {
            final_src.w += final_src.x;
            final_src.x = 0;
        }
        maxw = src->w - final_src.x;
        if (maxw < final_src.w)
            final_src.w = maxw;

        final_src.y = srcrect->y;
        final_src.h = srcrect->h;
        if (final_src.y < 0) {
            final_src.h += final_src.y;
            final_src.y = 0;
        }
        maxh = src->h - final_src.y;
        if (maxh < final_src.h)
            final_src.h = maxh;

    } else {
        final_src.x = final_src.y = 0;
        final_src.w = src->w;
        final_src.h = src->h;
    }

    /* clip the destination rectangle against the clip rectangle */
    if (dstrect) {
        int maxw, maxh;

        final_dst.x = dstrect->x;
        final_dst.w = dstrect->w;
        if (final_dst.x < 0) {
            final_dst.w += final_dst.x;
            final_dst.x = 0;
        }
        maxw = dst->w - final_dst.x;
        if (maxw < final_dst.w)
            final_dst.w = maxw;

        final_dst.y = dstrect->y;
        final_dst.h = dstrect->h;
        if (final_dst.y < 0) {
            final_dst.h += final_dst.y;
            final_dst.y = 0;
        }
        maxh = dst->h - final_dst.y;
        if (maxh < final_dst.h)
            final_dst.h = maxh;
    } else {
        final_dst.x = final_dst.y = 0;
        final_dst.w = dst->w;
        final_dst.h = dst->h;
    }

    if (final_dst.w > 0 && final_dst.h > 0) {
        return SDL_LowerBlitScaled(src, &final_src, dst, &final_dst);
    }

    return 0;
}
#endif