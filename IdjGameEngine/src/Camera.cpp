#include "pch.h"
#include "Camera.h"
#include "InputManager.h"

Vec2 Camera::pos(0, 0), Camera::speed(0, 0);
GameObject* Camera::focus = nullptr;


void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}


void Camera::Unfollow() {
    focus = nullptr;
}


void Camera::Update(float dt) {
    auto& inputManager = InputManager::GetInstance();

    if (focus != nullptr) {

        //TODO

    } else {
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
            speed.y = -dt;
            pos.y += speed.y;
        }
        if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
            speed.y = dt;
            pos.y += speed.y;
        }
        if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
            speed.x = -dt;
            pos.x += speed.x;
        }
        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
            speed.x = dt;
            pos.x += speed.x;
        }
    }
}
