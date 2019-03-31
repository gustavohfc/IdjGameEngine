#include "pch.h"
#include "Music.h"

Music::Music() {}


Music::Music(const std::string& file) {

    Open(file);
}


Music::~Music() {
    Mix_FreeMusic(music);
}


void Music::Play(int times) const {
    if (!IsOpen()) {
        throw std::logic_error("Trying to play a nullptr music");
    }

    auto mixPlayReturn = Mix_PlayMusic(music, times);
    if (mixPlayReturn != 0) {
        throw std::runtime_error(Mix_GetError());
    }
}


void Music::Stop(int msToStop) {
    auto success = Mix_FadeOutMusic(msToStop);
    if (!success) {
        throw std::runtime_error("Mix_FadeOutMusic fail");
    }
}


void Music::Open(const std::string& file) {
    if (IsOpen()) {
        Mix_FreeMusic(music);
    }

    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        throw std::runtime_error(Mix_GetError());
    }
}


bool Music::IsOpen() const {
    return music != nullptr;
}
