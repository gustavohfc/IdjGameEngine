#include "pch.h"
#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"


Sprite::Sprite(GameObject& associated):
    Component(associated) {}


Sprite::Sprite(GameObject& associated, const std::string& file):
    Sprite(associated) {

    Open(file);
}


void Sprite::Open(const std::string& file) {
    texture = Resources::GetImage(file);

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
    Render(associated.box.x - Camera::pos.x,
           associated.box.y - Camera::pos.y,
           associated.box.w,
           associated.box.h);
}


void Sprite::Update(float dt) {}


bool Sprite::Is(const std::string& type) {
    return type == "Sprite";
}
