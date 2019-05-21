#include "pch.h"
#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Text.h"
#include "Constants.h"
#include "Camera.h"


TitleState::TitleState() {
	auto background = std::make_shared<GameObject>();
	background->AddComponent<Sprite>("assets/img/title.jpg");
	objectArray.push_back(background);

	auto text = std::make_shared<GameObject>();
	text->AddComponent<Text>("assets/font/Call me maybe.ttf", 48, Text::BLENDED, "Pressione espaco para iniciar o jogo", Constants::Color::ORANGERED);
	text->box.SetCenter(512, 525);
	objectArray.push_back(text);

	// TODO: Show and hide the text
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
	Camera::Reset();
	StartArray();
}


void TitleState::Pause() {}

void TitleState::Resume() {
	Camera::Reset();
}
