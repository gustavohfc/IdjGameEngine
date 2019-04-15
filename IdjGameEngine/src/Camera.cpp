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

    if (focus != nullptr) {

        pos = focus->box.GetCenter();

    } else {

        auto& inputManager = InputManager::GetInstance();
        speed = { 0, 0 };

        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
            speed.y = -10;
        }

        if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
            speed.y = 10;
        }

        if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
            speed.x = -10;
        }

        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
            speed.x = 10;
        }

        pos += speed * dt;
    }
}
