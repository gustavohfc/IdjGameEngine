#include "pch.h"
#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"


Sprite::Sprite(GameObject& associated, const std::string& file, int frameCount, float frameTime) :
    Component(associated),
    frameCount(frameCount),
    currentFrame(0),
    timeElapsed(0),
    frameTime(0),
    scale({1, 1}) {

    Open(file);
}


void Sprite::Open(const std::string& file) {
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SetClip(0, 0, width, height);

    UpdateFrameClipRect();

    associated.box.w = GetWidth();
    associated.box.h = height;
}


void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = {x, y, w, h};
}


int Sprite::GetWidth() const {
    return (float(width) / frameCount) * scale.x;
}


int Sprite::GetHeight() const {
    return height * scale.y;
}


bool Sprite::IsOpen() const {
    return texture != nullptr;
}


void Sprite::Render(int x, int y, int w, int h) {
    auto renderer = Game::GetInstance().GetRenderer();

    SDL_Rect dst = {x, y, w, h};

    SDL_RenderCopyEx(renderer, texture, &clipRect, &dst, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}


void Sprite::SetScale(float scaleX, float scaleY) {
    scale = {scaleX, scaleY};

    associated.box.w = GetWidth();
    associated.box.h = GetHeight();
}


Vec2 Sprite::GetScale() const {
    return scale;
}


void Sprite::SetFrame(int frame) {
    currentFrame = frame;

    UpdateFrameClipRect();
}


void Sprite::SetFrameCount(int frameCount) {
    this->frameCount = frameCount;

    currentFrame = 0;

    UpdateFrameClipRect();
}


void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}


void Sprite::Start() {}


void Sprite::Render() {
    Render(associated.box.x - Camera::pos.x,
           associated.box.y - Camera::pos.y,
           associated.box.w,
           associated.box.h);
}


void Sprite::Update(float dt) {
    timeElapsed += dt;

    if (timeElapsed >= frameTime) {
        timeElapsed = 0;
        currentFrame = ++currentFrame % frameCount;
        UpdateFrameClipRect();
    }
}


bool Sprite::Is(const std::string& type) {
    return type == "Sprite";
}


void Sprite::UpdateFrameClipRect() {
    auto frameWidth = width / frameCount;
    auto x = currentFrame * frameWidth;

    SetClip(x, clipRect.y, frameWidth, clipRect.h);

    associated.box.w = GetWidth();
}
