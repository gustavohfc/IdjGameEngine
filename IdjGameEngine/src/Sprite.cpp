#include "pch.h"
#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() : texture(nullptr) {}


Sprite::Sprite(const std::string& file) : texture(nullptr) {
    Open(file);
}


Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}


void Sprite::Open(const std::string& file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    auto renderer = Game::GetInstance().GetRenderer();

    texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SetClip(0, 0, width, height);
}


void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}


void Sprite::Render(int x, int y) {
    auto renderer = Game::GetInstance().GetRenderer();

    SDL_Rect dst = {
        x,
        y,
        clipRect.w,
        clipRect.h
    };

    SDL_RenderCopy(renderer, texture, &clipRect, &dst);
}


int Sprite::GetWidth() const {
    return width;
}


int Sprite::GetHeight() const {
    return height;
}


bool Sprite::IsOpen() const {
    return texture != nullptr;
}
