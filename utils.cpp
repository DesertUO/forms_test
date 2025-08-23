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

void UIFrame::addButton(ButtonComponent* button) {
    this->buttons.emplace_back(button);
}

// TODO
inline int UIFrame::posToGrid(Vec2<float> pos) {
    return 1;
}


void UIFrame::update(const SDL_Event& e) {
    SDL_GetMouseState(&mousePos.x, &mousePos.y);

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

void UIFrame::render(SDL_Renderer* _renderer) {
    for(auto& button: buttons) {
        SDL_SetRenderDrawColor(_renderer, button->bg.r, button->bg.g, button->bg.b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(_renderer, &button->boundingBox);
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDebugText(_renderer, button->boundingBox.x, button->boundingBox.y, button->text.c_str());
    }
    SDL_RenderDebugTextFormat(_renderer, 0, 0, "Mouse pos: x: %f, y: %f", mousePos.x, mousePos.y);
}

