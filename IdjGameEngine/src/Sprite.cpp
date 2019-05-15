#include "pch.h"
#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"
#include <iterator>


Sprite::Sprite(GameObject& associated, const std::string& file, int frameCount, float frameTime, float secondsToSelfDestruct) :
    Component(associated),
    frameCount(frameCount),
    currentFrame(0),
    timeElapsed(0),
    frameTime(frameTime),
    scale({1, 1}),
    secondsToSelfDestruct(secondsToSelfDestruct) {

    Open(file);
}


void Sprite::Open(const std::string& file) {
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SetClip(0, 0, width, height);

    UpdateFrameClipRect();

    associated.box.w = float(GetWidth());
    associated.box.h = float(height);
}


void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = {x, y, w, h};
}


int Sprite::GetWidth() const {
    return int((float(width) / frameCount) * scale.x);
}


int Sprite::GetHeight() const {
    return int(height * scale.y);
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

    associated.box.w = float(GetWidth());
    associated.box.h = float(GetHeight());
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
    Render(int(associated.box.x - Camera::pos.x),
           int(associated.box.y - Camera::pos.y),
           int(associated.box.w),
           int(associated.box.h));
}


void Sprite::Update(float dt) {
    timeElapsed += dt;

    if (timeElapsed >= frameTime) {
        timeElapsed = 0;
        currentFrame = (currentFrame + 1) % frameCount;
        UpdateFrameClipRect();
    }

    if (secondsToSelfDestruct != 0) {
        selfDestructCount.Update(dt);
        if (selfDestructCount.Get() > secondsToSelfDestruct) {
            associated.RequestDelete();
        }
    }
}


ComponentType Sprite::GetType() const {
    return Type;
}


void Sprite::UpdateFrameClipRect() {
    auto frameWidth = width / frameCount;
    auto x = currentFrame * frameWidth;

    SetClip(x, clipRect.y, frameWidth, clipRect.h);

    associated.box.w = float(GetWidth());
}
