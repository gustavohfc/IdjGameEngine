#include "pch.h"
#include "State.h"


State::State(): bg("resources/img/ocean.jpg"),
                music("resources/audio/stageState.ogg"),
                quitRequested(false) {
    music.Play();
}


bool State::QuitRequested() const {
    return quitRequested;
}


void State::LoadAssets() {}


void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}


void State::Render() {
    bg.Render(0, 0);
}
