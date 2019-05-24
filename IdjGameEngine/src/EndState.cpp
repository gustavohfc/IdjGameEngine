#include "pch.h"
#include "EndState.h"
#include "GameData.h"
#include "Sprite.h"
#include "Camera.h"
#include "InputManager.h"
#include "Game.h"
#include "Text.h"


EndState::EndState():
	backgroundMusic(GameData::playerVictory ? "assets/audio/endStateWin.ogg" : "assets/audio/endStateLose.ogg"){

	auto background = std::make_shared<GameObject>();
	background->AddComponent<Sprite>(GameData::playerVictory ? "assets/img/win.jpg" : "assets/img/lose.jpg");
	objectArray.push_back(background);

	auto text = std::make_shared<GameObject>();
	text->AddComponent<Text>("assets/font/Call me maybe.ttf", 36, Text::BLENDED, "Pressione espaco para reiniciar o jogo ou esc para sair", Constants::Color::ORANGERED);
	text->box.SetCenter(512, 525);
	objectArray.push_back(text);

	backgroundMusic.Play();
}


EndState::~EndState() {}

void EndState::LoadAssets() {}

void EndState::Update(float dt) {
	auto& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested() || inputManager.IsKeyDown(SDLK_ESCAPE);

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
