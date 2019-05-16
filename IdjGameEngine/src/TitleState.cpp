#include "pch.h"
#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "CameraFollower.h"


TitleState::TitleState() {
	auto background = std::make_shared<GameObject>();
	background->AddComponent(std::make_shared<Sprite>(*background, "assets/img/title.jpg"));
	background->AddComponent(std::make_shared<CameraFollower>(*background));
	objectArray.push_back(background);
}


TitleState::~TitleState() {}

void TitleState::LoadAssets() {}


void TitleState::Update(float dt) {
	auto& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();

	if (inputManager.IsKeyDown(SDLK_SPACE)) {
		Game::GetInstance().Push(new StageState());
	}

	UpdateArray(dt);
}


void TitleState::Render() {
	RenderArray();
}


void TitleState::Start() {
	StartArray();
}


void TitleState::Pause() {}

void TitleState::Resume() {}
