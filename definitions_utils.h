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
    double                          x;
    double                          y;
    double                          w;
    double                          h;
};

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

using uint8 = unsigned char;

struct Event {};

bool PointInFRect(const SDL_FRect* rect, Vec2<float> pos);
