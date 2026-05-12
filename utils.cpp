#include "utils.h"

bool PointInFRect(const SDL_FRect* rect, Vec2<float> pos) {
    return (pos.x >= rect->x &&
            pos.x <= rect->x + rect->w &&
            pos.y >= rect->y &&
            pos.y <= rect->y + rect->h);
}

UIFrame::UIFrame() {
    this->buttons = {};
}

UIFrame::~UIFrame() {
}

void UIFrame::addComponent(UIComponent* component) {
    components.emplace_back(component);
    ButtonComponent* button = static_cast<ButtonComponent*>(component);
    if(button) {
       buttons.emplace_back(button);
    }
}

inline int coordToIndex(const int& x, const int& y, const int& width, const int& height) {
    if(x > width || y > height) {
        SDL_Log("Warning: Cordinates given are out of range of matrix");
    }
    return y * width + x;
}

// TODO
inline int UIFrame::posToGrid(const Vec2<float>& pos) {
    int x = (int) pos.x / gridSize;
    int y = (int) pos.y / gridSize;
    return coordToIndex(x, y, gridDim.x, gridDim.y);
}


void UIFrame::updateGridDims() {
    gridDim.x = (int) winSize.x / gridSize + 1;
    gridDim.y = (int) winSize.y / gridSize + 1;
}

void UIFrame::update(const SDL_Event& e) {
    SDL_GetMouseState(&mousePos.x, &mousePos.y);

    updateGridDims();

    if(!inFocus.empty()) {
        static_cast<ButtonComponent*>(inFocus.at(0))->whileFocus();
    }

    for(auto button = buttons.rbegin(); button != buttons.rend(); ++button) {
        if(PointInFRect(&(*button)->boundingBox, mousePos)) {
            (*button)->onHover();
            break;
        }
    }

    if(e.type == SDL_EVENT_MOUSE_MOTION) {
        float xrel = e.motion.xrel;
        float yrel = e.motion.yrel;
        for(auto& button : buttons) {
            if(!button->hasBeenClicked) { continue; }
            // Enable just for draggable objects
            continue;
            button->boundingBox.x += xrel;
            button->boundingBox.y += yrel;
        }
    }
    if(e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        float bX = e.button.x;
        float bY = e.button.y;
        bool buttonClicked = false;
        for(auto button = buttons.rbegin(); button != buttons.rend(); ++button) {
            if(PointInFRect(&(*button)->boundingBox, Vec2<float>{bX, bY})) {
                buttonClicked = true;
                if(inFocus.empty()) {
                    inFocus.emplace_back(*button);
                }
                else {
                    if(*button != inFocus.at(0)) {
                        inFocus.pop_back();
                        inFocus.emplace_back(*button);
                        (*button)->onFocus();
                    }
                }
                if(e.button.button == LEFT_CLICK) {
                    (*button)->hasBeenClicked = true;
                    (*button)->onClick();
                    break;
                }
                if(e.button.button == RIGHT_CLICK) {
                    (*button)->onRightClick();
                    break;
                }
                break;
            }
        }
        if(!buttonClicked && !inFocus.empty()) { inFocus.pop_back(); }
    }
    if(e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        for(auto& button : buttons) {
            if(button->hasBeenClicked) {
                button->hasBeenClicked = false;
                button->onRelease();
            }
        }
    }
}

void UIFrame::renderGrid(SDL_Renderer* _renderer) {
    SDL_Color prevColor;
    SDL_GetRenderDrawColor(_renderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    // Horizontal
    for(int i = 1; i < gridDim.x; i++) {
        SDL_RenderLine(_renderer, i*gridSize, 0, i*gridSize, winSize.y);
    }
    // Vertial
    for(int i = 1; i < gridDim.y; i++) {
        SDL_RenderLine(_renderer, 0, i*gridSize, winSize.x, i*gridSize);
    }
    SDL_SetRenderDrawColor(_renderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
}

void UIFrame::render(SDL_Renderer* _renderer) {
    renderGrid(_renderer);
    for(auto& button: buttons) {
        SDL_SetRenderDrawColor(_renderer, button->bg.r, button->bg.g, button->bg.b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(_renderer, &button->boundingBox);
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDebugText(_renderer, button->boundingBox.x, button->boundingBox.y, button->text.c_str());
    }
    SDL_RenderDebugTextFormat(_renderer, 0, 0, "Mouse pos: x: %f, y: %f", mousePos.x, mousePos.y);
}

