#pragma once
#include <variant>
#include "../definitions_utils.h"

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

enum class UIStyleProperty {
    BACKGROUND_COLOR,
    COLOR,
    BORDER_SIZE,
    BORDER_COLOR,
    BORDER_RADIUS,
    TEXT_CONTENT,
    OPACITY,
};

using UIStylePrimitive = std::variant<float, int, uint8, string, Color>;

using UIStyleBlock = unordered_map<UIStyleProperty, UIStylePrimitive>;

class UIComponent {
    public:
        UIComponent();

        Rec2                            bounds;
        UIComponentState                state = NORMAL;
        UIComponent*                    parent;
        vector<UIComponent*>            children;
        // vvector<std::shared_ptr<UIComponent>>   children;
        // The code above is to change the old
        // manual memory management ti smart pointers
        // The main vector of children is children
        // with the main shared_ptr and any other
        // vector of specific types of components
        // will use weak_ptr to be able to just delete
        // any component and not worry about having
        // obsolete pointers in other vectors which would
        // cause undefined behaviour or segmentation
        // faults.

        /*
        virtual void layout() = 0;

        virtual void handle_event(Event e) = 0;

        virtual void draw() = 0;
        */
};

class UIFrameComponent : public UIComponent {
    public:
        UIFrameComponent();

        SDL_FRect                       boundingBox;
        SDL_Color                       bg;
};

class UIButtonComponent : public UIComponent {
    public:
        UIButtonComponent();

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
            prevText = content;
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
