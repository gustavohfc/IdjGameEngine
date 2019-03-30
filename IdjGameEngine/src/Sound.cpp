#include "pch.h"
#include "Sound.h"


Sound::Sound(GameObject& associated):
    Component(associated) {}


Sound::Sound(GameObject& associated, std::string file):
    Sound(associated) {

    Open(file);
}


Sound::~Sound() {
    if (IsOpen()) {
        Stop();
        Mix_FreeChunk(chunk);
    }
}


void Sound::Play(int times) {
    if (!IsOpen()) {
        throw std::logic_error("Trying to play a nullptr chunk");
    }

    channel = Mix_PlayChannel(-1, chunk, times - 1);
    if (channel == -1) {
        throw std::runtime_error("Mix_PlayChannel fail");
    }
}


void Sound::Stop() {
    if (!IsOpen()) {
        throw std::logic_error("Trying to stop a nullptr chunk");
    }

    Mix_HaltChannel(channel);
}


void Sound::Open(std::string file) {
    chunk = Mix_LoadWAV(file.c_str());
    if (chunk == nullptr) {
        throw std::runtime_error(Mix_GetError());
    }
}


bool Sound::IsOpen() {
    return chunk != nullptr;
}


void Sound::Update(float dt) {}

void Sound::Render() {}


bool Sound::Is(std::string type) {
    return type == "Sound";
}
