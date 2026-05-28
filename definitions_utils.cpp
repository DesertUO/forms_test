#include "definitions_utils.h"

bool PointInFRect(const SDL_FRect* rect, Vec2<float> pos) {
    return (pos.x >= rect->x &&
            pos.x <= rect->x + rect->w &&
            pos.y >= rect->y &&
            pos.y <= rect->y + rect->h);
}
