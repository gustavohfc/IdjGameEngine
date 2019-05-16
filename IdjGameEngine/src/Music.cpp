#include "pch.h"
#include "Music.h"
#include "Resources.h"

Music::Music() {}


Music::Music(const std::string& file) {

	Open(file);
}


void Music::Play(int times) const {
	if (!IsOpen()) {
		throw std::logic_error("Trying to play a nullptr music");
	}

	auto mixPlayReturn = Mix_PlayMusic(music.get(), times);
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
	music = Resources::GetMusic(file);
}


bool Music::IsOpen() const {
	return music != nullptr;
}
