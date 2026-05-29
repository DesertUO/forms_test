#include "definitions_utils.h"

bool PointInFRect(const Rec2* rect, Vec2<float> pos) {
    return (pos.x >= rect->x &&
            pos.x <= rect->x + rect->w &&
            pos.y >= rect->y &&
            pos.y <= rect->y + rect->h);
}

SDL_FRect Rec2ToSDLFRect(const Rec2& rec) {
    SDL_FRect newRec = {
        rec.x, rec.y,
        rec.w, rec.h
    };
    return newRec;
}
