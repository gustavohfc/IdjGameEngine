#include "pch.h"
#include "EndState.h"
#include "GameData.h"
#include "Sprite.h"
#include "Camera.h"
#include "InputManager.h"
#include "Game.h"


EndState::EndState() {
	// TODO: Add sound and text

	auto background = std::make_shared<GameObject>();
	background->AddComponent(std::make_shared<Sprite>(*background, GameData::playerVictory ? "assets/img/win.jpg" : "assets/img/lose.jpg"));
	objectArray.push_back(background);
}


EndState::~EndState() {}

void EndState::LoadAssets() {}

void EndState::Update(float dt) {
	auto& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	if (inputManager.IsKeyDown(SDLK_SPACE)) {
		popRequested = true;
	}

	UpdateArray(dt);
}

void EndState::Render() {
	RenderArray();
}


void EndState::Start() {
	Camera::Reset();
	StartArray();
}


void EndState::Pause() {}


void EndState::Resume() {
	Camera::Reset();
}
