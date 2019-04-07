#include "pch.h"
#include "Sprite.h"
#include "Game.h"


Sprite::Sprite(GameObject& associated):
    Component(associated) {}


Sprite::Sprite(GameObject& associated, const std::string& file):
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
    clipRect = {x, y, w, h};
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


void Sprite::Render(int x, int y, int w, int h) {
    auto renderer = Game::GetInstance().GetRenderer();

    SDL_Rect dst = {x, y, w, h};

    SDL_RenderCopy(renderer, texture, &clipRect, &dst);
}


void Sprite::Render() {
    Render(associated.box.x, associated.box.y, associated.box.w, associated.box.h);
}


void Sprite::Update(float dt) {}


bool Sprite::Is(const std::string& type) {
    return type == "Sprite";
}
