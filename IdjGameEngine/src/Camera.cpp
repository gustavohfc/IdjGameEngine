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

        auto focusCenter = focus->box.GetCenter();

        pos.x = focusCenter.x - 1024 / 2;
        pos.y = focusCenter.y - 600 / 2;

    } else {

        auto& inputManager = InputManager::GetInstance();
        speed = {0, 0};

        if (inputManager.IsKeyDown(UP_ARROW_KEY)) {
            speed.y = -100;
        }

        if (inputManager.IsKeyDown(DOWN_ARROW_KEY)) {
            speed.y = 100;
        }

        if (inputManager.IsKeyDown(LEFT_ARROW_KEY)) {
            speed.x = -100;
        }

        if (inputManager.IsKeyDown(RIGHT_ARROW_KEY)) {
            speed.x = 100;
        }

        pos += speed * dt;
    }
}
