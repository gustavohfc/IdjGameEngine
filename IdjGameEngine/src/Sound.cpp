#include "pch.h"
#include "Sound.h"
#include "Resources.h"


Sound::Sound(GameObject& associated):
    Component(associated) {}


Sound::Sound(GameObject& associated, const std::string& file):
    Sound(associated) {

    Open(file);
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

    channel = -1;
}


void Sound::Open(const std::string& file) {
    chunk = Resources::GetSound(file);
}


bool Sound::IsOpen() {
    return chunk != nullptr;
}


bool Sound::IsPlaying() const {
    if (channel == -1) {
        return false;
    }

    return Mix_Playing(channel);
}


void Sound::Update(float dt) {}

void Sound::Render() {}


bool Sound::Is(const std::string& type) {
    return type == "Sound";
}
