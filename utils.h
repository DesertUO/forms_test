#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

using std::string;
using std::vector;
using std::unordered_map;

template < typename T >
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

#define LEFT_CLICK                  1
#define MIDDLE_CLICK                2
#define RIGHT_CLICK                 3
#define AUX_1_CLICK                 4
#define AUX_2_CLICK                 5

struct UIComponent {
};

struct UIFrameComponent : UIComponent {
    SDL_FRect                       boundingBox;
    SDL_Color                       bg;
    vector<UIComponent*>            children;
};

struct ButtonComponent : UIComponent{
    string                          text;
    string                          prevText;
    SDL_FRect                       boundingBox;
    SDL_Color                       bg;
    SDL_Color                       prevBg;
    bool                            hasBeenClicked = false;

    virtual void onClick() {
        prevText = text;
        text = "Button clicked!";
        prevBg = bg;
        bg = SDL_Color{100, 100, 100, SDL_ALPHA_OPAQUE};
    };
    virtual void onRelease() {
        text = prevText;
        bg = prevBg;
    };
    virtual void onRightClick() {
        SDL_Log("ASd");
    }
    virtual void onRightRelease() {}
    virtual void onHover() {};
    virtual void onFocus() {};
    virtual void onLostFocus() {};
};

bool PointInFRect(const SDL_FRect* rect, Vec2<float> pos);

#define GRID_SIZE 100.0f

class UIFrame {
    private:
        Vec2<float>                 mousePos;
        vector<UIComponent*>        components;
        vector<ButtonComponent*>    buttons;
    public:
        Vec2<int>                   winSize;

        UIFrame();
        ~UIFrame();

        void addButton(ButtonComponent* button);

        void update(const SDL_Event& e);
        void render(SDL_Renderer* _renderer);

        int posToGrid(Vec2<float> pos);
};


