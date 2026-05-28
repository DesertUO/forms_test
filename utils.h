#pragma once
#include <SDL3/SDL.h>
#include "components/components.h"


#define GRID_SIZE 100.0f

class UIFrame {
    private:
        Vec2<float>                 mousePos;
        vector<UIComponent*>        components;
        vector<UIButtonComponent*>    buttons;
        vector<UIComponent*>        inFocus;
        Vec2<int>                   gridDim;
        float                       gridSize = 500.0f;
        matrix<UIButtonComponent*>    grid;
    public:
        Vec2<int>                   winSize;

        UIFrame();
        ~UIFrame();

        void addComponent(UIComponent* component);

        void update();
        void render(SDL_Renderer* _renderer);

        void handleEvent(const SDL_Event& e);

        void renderGrid(SDL_Renderer* _renderer);

        void updateGridDims();
        int posToGrid(const Vec2<float>& pos);
};
