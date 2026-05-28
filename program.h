#pragma once
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <cmath>
#include "utils.h"

// This is a macro, do you see it? lol
// This is an fucking actual macro boi
#define getColor(color) color.r, color.g, color.b,  color.a

class Program {
    private:
        SDL_Window*                 _window;
        SDL_Renderer*               _renderer;
        bool                        isRunning;
        double                      counter;
        UIFrame*                    uiFrame;

    public:
        Program();
        ~Program();

        void init();
        void run();
        void stop();

        void update();
        void render();

        void handleEvent(const SDL_Event& event);
};
