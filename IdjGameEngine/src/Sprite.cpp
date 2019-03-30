#include "pch.h"
#include "Sprite.h"
#include "Game.h"


Sprite::Sprite(GameObject& associated):
    Component(associated),
    texture(nullptr) {}


Sprite::Sprite(GameObject& associated, std::string file):
    Sprite(associated) {

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
    associated.box.w = width;
    associated.box.h = height;
}


void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
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


void Sprite::Render() {
    auto renderer = Game::GetInstance().GetRenderer();

    SDL_Rect dst = {
        (int)associated.box.x,
        (int)associated.box.y,
        (int)associated.box.w,
        (int)associated.box.h
    };

    SDL_RenderCopy(renderer, texture, &clipRect, &dst);
}


void Sprite::Update(float dt) {}


bool Sprite::Is(std::string type) {
    return type == "Sprite";
}
