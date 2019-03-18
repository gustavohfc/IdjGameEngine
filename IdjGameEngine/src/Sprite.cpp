#include "Sprite.h"
#include "SDL_image.h"
#include "Game.h"

Sprite::Sprite(): texture(nullptr) {}


Sprite::Sprite(std::string file) {
    texture = nullptr;
    Open(file);
}


Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}


void Sprite::Open(std::string file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    // TODO
    auto renderer = Game::GetInstance().GetRenderer();

    texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr) {
        throw std::exception(SDL_GetError());
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}


void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}


void Sprite::Render(int x, int y) {
    // TODO
    auto renderer = Game::GetInstance().GetRenderer();

    SDL_Rect dst = {
        x,
        y,
        clipRect.w,
        clipRect.h
    };

    SDL_RenderCopy(renderer, texture, &clipRect, &dst);
}


int Sprite::GetWidth() {
    return width;
}


int Sprite::GetHeight() {
    return height;
}


bool Sprite::IsOpen() {
    return texture != nullptr;
}
