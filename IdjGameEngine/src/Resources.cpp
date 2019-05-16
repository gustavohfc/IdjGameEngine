#include "pch.h"
#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;


std::shared_ptr<SDL_Texture> Resources::GetImage(const std::string& file) {
	auto it = imageTable.find(file);

	if (it != imageTable.end()) {
		return it->second;
	}

	// Load image
	auto renderer = Game::GetInstance().GetRenderer();

	auto texture = IMG_LoadTexture(renderer, file.c_str());
	if (texture == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}

	imageTable[file] = std::shared_ptr<SDL_Texture>(texture, [](SDL_Texture* p) { SDL_DestroyTexture(p); });

	return imageTable[file];
}


std::shared_ptr<Mix_Music> Resources::GetMusic(const std::string& file) {
	auto it = musicTable.find(file);

	if (it != musicTable.end()) {
		return it->second;
	}

	// Load music
	auto music = Mix_LoadMUS(file.c_str());
	if (music == nullptr) {
		throw std::runtime_error(Mix_GetError());
	}

	musicTable[file] = std::shared_ptr<Mix_Music>(music, [](Mix_Music* p) { Mix_FreeMusic(p); });

	return musicTable[file];
}


std::shared_ptr<Mix_Chunk> Resources::GetSound(const std::string& file) {
	auto it = soundTable.find(file);

	if (it != soundTable.end()) {
		return it->second;
	}

	// Load chunk
	auto chunk = Mix_LoadWAV(file.c_str());
	if (chunk == nullptr) {
		throw std::runtime_error(Mix_GetError());
	}

	soundTable[file] = std::shared_ptr<Mix_Chunk>(chunk, [](Mix_Chunk* p) { Mix_FreeChunk(p); });

	return soundTable[file];
}


void Resources::ClearImages() {
	for (auto&& it = imageTable.begin(); it != imageTable.end();) {
		if (it->second.unique()) {
			it = imageTable.erase(it);
		} else {
			++it;
		}
	}
}


void Resources::ClearMusics() {
	for (auto&& it = musicTable.begin(); it != musicTable.end();) {
		if (it->second.unique()) {
			it = musicTable.erase(it);
		} else {
			++it;
		}
	}
}


void Resources::ClearSounds() {
	for (auto&& it = soundTable.begin(); it != soundTable.end();) {
		if (it->second.unique()) {
			it = soundTable.erase(it);
		} else {
			++it;
		}
	}
}
