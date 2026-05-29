#pragma once
#include <SDL3/SDL.h>
#include "components/components.h"


#define GRID_SIZE 100.0f

class UIFrame {
    private:
        Vec2<float>                                 mousePos;
        vector<std::unique_ptr<UIComponent>>        components;
        vector<UIButtonComponent*>                  buttons;
        vector<UIComponent*>                        inFocus;
        Vec2<int>                                   gridDim;
        float                                       gridSize = 500.0f;
    public:
        Vec2<int>                   winSize;

        UIFrame();
        ~UIFrame() = default;

        void addComponent(std::unique_ptr<UIComponent> component);

        void update();
        void render(SDL_Renderer* _renderer);

        void handleEvent(const SDL_Event& e);

        void renderGrid(SDL_Renderer* _renderer);

        void updateGridDims();
        int posToGrid(const Vec2<float>& pos);
};
