#include "pch.h"
#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;


SDL_Texture* Resources::GetImage(const std::string& file) {
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

    imageTable[file] = texture;

    return texture;
}


Mix_Music* Resources::GetMusic(const std::string& file) {
    auto it = musicTable.find(file);

    if (it != musicTable.end()) {
        return it->second;
    }

    // Load music
    auto music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        throw std::runtime_error(Mix_GetError());
    }

    musicTable[file] = music;

    return music;
}


Mix_Chunk* Resources::GetSound(const std::string& file) {
    auto it = soundTable.find(file);

    if (it != soundTable.end()) {
        return it->second;
    }

    // Load chunk
    auto chunk = Mix_LoadWAV(file.c_str());
    if (chunk == nullptr) {
        throw std::runtime_error(Mix_GetError());
    }

    soundTable[file] = chunk;

    return chunk;
}


void Resources::ClearImages() {
    for (auto&& i : imageTable) {
        SDL_DestroyTexture(i.second);
    }
}


void Resources::ClearMusics() {
    for (auto&& i : musicTable) {
        Mix_FreeMusic(i.second);
    }
}


void Resources::ClearSounds() {
    for (auto&& i : soundTable) {
        Mix_FreeChunk(i.second);
    }
}
