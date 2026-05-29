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

    // Will not work for now
    // UIFrameComponent* bg_comp = new UIFrameComponent();
    // bg_comp->boundingBox = SDL_FRect{0, 0, 1000, 1000};
    // bg_comp->bg = SDL_Color{10, 10, 10, SDL_ALPHA_OPAQUE};
    // as it still needs implementation
    // uiFrame->addComponent(bg_comp);

    // Test buttons
    auto b1 = std::make_unique<UIButtonComponent>();;
    b1->text = "ASd";
    b1->bounds = Rec2{ 200.0f, 100.0f, 100.0f, 100.0f};
    uiFrame->addComponent(std::move(b1));

    auto b2 = std::make_unique<UIButtonComponent>();
    b2->text = "Testt";
    b2->bounds = Rec2{ 250.0f, 150.0f, 100.0f, 100.0f};
    uiFrame->addComponent(std::move(b2));

    while(isRunning) {
        SDL_Log("Tick: %d", ((counter % 20) + 1));

        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            this->handleEvent(e);
            uiFrame->handleEvent(e);
        }
        this->update();
        this->render();
        counter++;
        SDL_Delay(50);
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

