#include "Music.h"

Music::Music(): music(nullptr) {}


Music::Music(std::string file) {
    music = nullptr;
    Open(file);

    // TODO
    Play();
}


Music::~Music() {
    Mix_FreeMusic(music);
}


void Music::Play(int times) {
    // TODO: music == nullptr
    auto mixPlayReturn = Mix_PlayMusic(music, -1);
    if (mixPlayReturn != 0) {
        throw std::exception(Mix_GetError());
    }
}


void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}


void Music::Open(std::string file) {
    // TODO Close music if already opened?
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        throw std::exception(Mix_GetError());
    }
}


bool Music::IsOpen() {
    return music != nullptr;
}
