#pragma once
#include <variant>
#include <memory>
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

/*
 * Test
 * UIStyleBlock DefaultUIStyles = {
 *     {UIStyleProperty::BACKGROUND_COLOR, Color{100, 100, 100}}
 * };
*/

class UIComponent {
    public:
        UIComponent();
        virtual ~UIComponent() = default;

        bool                                    isDirty = false;
        Rec2                                    bounds;
        Vec2<float>                             cacheGlobalPos;

        UIComponentState                        state = NORMAL;
        UIComponent*                            parent;
        vector<std::unique_ptr<UIComponent>>    children;

        UIStyleBlock                            styles;

        /*
        virtual void layout() = 0;

        virtual void handle_event(Event e) = 0;

        virtual void draw() = 0;
        */
};

class UIFrameComponent : public UIComponent {
    public:
        UIFrameComponent();

        SDL_Color                       bg;
};

class UIButtonComponent : public UIComponent {
    public:
        UIButtonComponent();

        string                          text;
        string                          prevText;
        string                          content;
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
            // SDL_Log("ASd, Right click!");
        }
        virtual void onRightRelease() {
            // SDL_Log("Rich click release");
        }
        virtual void onHover() {
            // SDL_Log("Hovered... %s", text.c_str());
        };
        virtual void onFocus() {};
        virtual void whileFocus() {
            // SDL_Log("On focus...%s", text.c_str());
        };
        virtual void onLostFocus() {};
};
