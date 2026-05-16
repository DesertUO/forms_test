#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>

using std::string;
using std::vector;
using std::unordered_map;

template < typename T >
using matrix = vector<vector<T>>;

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

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

using uint8 = unsigned char;

struct Event {};

#define LEFT_CLICK                  1
#define MIDDLE_CLICK                2
#define RIGHT_CLICK                 3
#define AUX_1_CLICK                 4
#define AUX_2_CLICK                 5

enum UIComponentState {
    NORMAL,
    LEFT_CLICKED,
    RIGHT_CLICKED,
    HOVERED,
    FOCUSED
};

class UIComponent {
    public:
        Rec2                            bounds;
        UIComponentState                state = NORMAL;
        UIComponent*                    parent;
        vector<UIComponent*>            children;

        virtual void layout() = 0;

        virtual void handle_event(Event e) = 0;
        
        virtual void draw() = 0;
};

enum class UIStyleProperty {
    BACKGROUND_COLOR,
    BORDER_SIZE,
    BORDER_COLOR,
    TEXT_CONTENT,
};

using UIStylePrimitive = std::variant<float, int, uint8, string, Color>;

using UIStyleBlock = unordered_map<UIStyleProperty, UIStylePrimitive>;

struct UIFrameComponent : UIComponent {
    SDL_FRect                       boundingBox;
    SDL_Color                       bg;
};

struct FrameComponent : UIComponent {
    SDL_Color                       bg;
    string                          path_to_bg;
    bool                            image_bg;
};

struct ButtonComponent : UIComponent {
    UIComponentState                state = NORMAL;
    string                          text;
    string                          prevText;
    string                          content;
    SDL_FRect                       boundingBox;
    SDL_Color                       bg             = SDL_Color{100, 100, 100, SDL_ALPHA_OPAQUE};
    SDL_Color                       prevBg;
    bool                            hasBeenClicked = false;

    virtual void onClick() {
        content = text;
        text = "Button clicked!";
        prevBg = bg;
        bg = SDL_Color{50, 50, 50, SDL_ALPHA_OPAQUE};
    };
    virtual void onRelease() {
        text = prevText;
        bg = prevBg;
    };
    virtual void onRightClick() {
        SDL_Log("ASd");
    }
    virtual void onRightRelease() {}
    virtual void onHover() {
        SDL_Log("Hovered... %s", text.c_str());
    };
    virtual void onFocus() {};
    virtual void whileFocus() {
        SDL_Log("On focus...%s", text.c_str());
    };
    virtual void onLostFocus() {};
};

bool PointInFRect(const SDL_FRect* rect, Vec2<float> pos);

#define GRID_SIZE 100.0f

class UIFrame {
    private:
        Vec2<float>                 mousePos;
        vector<UIComponent*>        components;
        vector<ButtonComponent*>    buttons;
        vector<UIComponent*>        inFocus;
        Vec2<int>                   gridDim;
        float                       gridSize = 500.0f;
        matrix<ButtonComponent*>    grid;
    public:
        Vec2<int>                   winSize;

        UIFrame();
        ~UIFrame();

        void addComponent(UIComponent* component);

        void update(const SDL_Event& e);
        void render(SDL_Renderer* _renderer);

        void renderGrid(SDL_Renderer* _renderer);

        void updateGridDims();
        int posToGrid(const Vec2<float>& pos);
};


