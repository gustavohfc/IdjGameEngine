#include "pch.h"
#include "Camera.h"
#include "InputManager.h"
#include "Constants.h"

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

		pos.x = focusCenter.x - Constants::Game::WINDOW_WIDTH / 2;
		pos.y = focusCenter.y - Constants::Game::WINDOW_HEIGHT / 2;

	} else {

		auto& inputManager = InputManager::GetInstance();
		speed = {0, 0};

		if (inputManager.IsKeyDown(UP_ARROW_KEY)) {
			speed.y -= Constants::Camera::SPEED;
		}

		if (inputManager.IsKeyDown(DOWN_ARROW_KEY)) {
			speed.y += Constants::Camera::SPEED;
		}

		if (inputManager.IsKeyDown(LEFT_ARROW_KEY)) {
			speed.x -= Constants::Camera::SPEED;
		}

		if (inputManager.IsKeyDown(RIGHT_ARROW_KEY)) {
			speed.x += Constants::Camera::SPEED;
		}

		pos += speed * dt;
	}
}


void Camera::Reset() {
	focus = nullptr;
	pos = { 0, 0 };
	speed = { 0, 0 };
}
