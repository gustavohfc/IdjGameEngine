#include "pch.h"
#include "State.h"


State::State(): bg("assets/img/ocean.jpg"),
                music("assets/audio/stageState.ogg"),
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
