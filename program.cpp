#include "program.h"

Program::Program() {
    uiFrame = new UIFrame();
}

Program::~Program() {
    delete uiFrame;

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

void Program::init() {
    if(SDL_Init(SDL_INIT_VIDEO) == false) {
        SDL_Log("Failed initializing SDL3: %s", SDL_GetError());
    }

    _window = SDL_CreateWindow("Test", 1080, 720, SDL_WINDOW_RESIZABLE);
    if(!_window) {
        SDL_Log("Error while initializing SDL_Window: %s", SDL_GetError());
    }

    _renderer = SDL_CreateRenderer(_window, NULL);
    if(!_renderer) {
        SDL_Log("Error while initializing SDL_Renderer: %s", SDL_GetError());
    }
}

void Program::run() {
    isRunning = true;
    counter = 0;

    UIFrameComponent* bg_comp = new UIFrameComponent();
    bg_comp->boundingBox = SDL_FRect{0, 0, 1000, 1000};
    bg_comp->bg = SDL_Color{10, 10, 10, SDL_ALPHA_OPAQUE};

    // Test buttons
    UIButtonComponent* b1 = new UIButtonComponent();
    b1->text = "ASd";
    b1->boundingBox = SDL_FRect{ 200.0f, 100.0f, 100.0f, 100.0f};
    uiFrame->addComponent(b1);

    UIButtonComponent* b2 = new UIButtonComponent();
    b2->text = "Testt";
    b2->boundingBox = SDL_FRect{ 250.0f, 150.0f, 100.0f, 100.0f};
    uiFrame->addComponent(b2);

    while(isRunning) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            this->handleEvent(e);
            uiFrame->handleEvent(e);
        }
        this->update();
        this->render();
    }
}

void Program::stop() {
    this->isRunning = false;
}

void Program::handleEvent(const SDL_Event& event) {
    switch(event.type) {
        case SDL_EVENT_QUIT:
            this->stop();
            break;
    }
}

void  Program::update() {
    SDL_GetWindowSize(_window, &uiFrame->winSize.x, &uiFrame->winSize.y);
    uiFrame->update();
}

void Program::render() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_renderer);
    uiFrame->render(_renderer);
    SDL_RenderPresent(_renderer);
}

