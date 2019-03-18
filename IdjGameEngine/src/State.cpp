#include "State.h"
#include "SDL.h"


State::State(): bg("resources/img/ocean.jpg"),
                music("resources/audio/stageState.ogg"),
                quitRequested(false) {}


bool State::QuitRequested() {
    return quitRequested;
}


void State::LoadAssets() {
    // bg.Open("resources/img/ocean.jpg");
}


void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}


void State::Render() {
    bg.Render(10, 10);
}
