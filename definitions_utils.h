#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

using std::string;
using std::vector;
using std::unordered_map;

template <typename T>
using matrix = vector<vector<T>>;

template <typename T>
struct Vec2 {
    T                               x;
    T                               y;
};

struct Rec2 {
    float                           x;
    float                           y;
    float                           w;
    float                           h;
};

struct Color {
    unsigned char                   r;
    unsigned char                   g;
    unsigned char                   b;
};

using uint8 = unsigned char;

struct Event {};

bool PointInFRect(const Rec2* rect, Vec2<float> pos);

SDL_FRect Rec2ToSDLFRect(const Rec2& rec);
