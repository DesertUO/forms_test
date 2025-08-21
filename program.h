#pragma once
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <cmath>
#include "utils.h"

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

        void update(const SDL_Event& event);
        void render();
};
