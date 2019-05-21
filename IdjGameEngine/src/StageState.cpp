#include "pch.h"
#include "StageState.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.h"
#include "Util.h"
#include "Collider.h"
#include "Constants.h"
#include "GameData.h"
#include "Game.h"
#include "EndState.h"


StageState::StageState():
	backgroundMusic("assets/audio/stageState.ogg") {

	auto background = std::make_shared<GameObject>();
	background->AddComponent<Sprite>("assets/img/ocean.jpg");
	background->AddComponent<CameraFollower>();
	objectArray.push_back(background);

	auto map = std::make_shared<GameObject>();
	auto tileSet = std::make_shared<TileSet>(*map, Constants::TileSet::TILE_WIDTH, Constants::TileSet::TILE_HEIGHT,
	                                         "assets/img/tileset.png");
	map->AddComponent<TileMap>("assets/map/tileMap.txt", tileSet);
	objectArray.push_back(map);

	for (auto i = 0; i < Constants::Alien::NUMBER_OF_ALIENS; i++) {
		auto x = rand() % 1408;
		auto y = rand() % 1280;
		auto offset = (rand() % 20) / 10.0;

		auto alienGO = std::make_shared<GameObject>();
		alienGO->AddComponent<Alien>(Constants::Alien::NUMBER_OF_MINIONS, offset);
		alienGO->box.SetCenter(x, y);
		objectArray.push_back(alienGO);
	}

	auto penguinBodyGO = std::make_shared<GameObject>();
	penguinBodyGO->AddComponent<PenguinBody>();
	penguinBodyGO->box.SetCenter(Constants::PenguinBody::INITIAL_POSITION_X, Constants::PenguinBody::INITIAL_POSITION_Y);
	objectArray.push_back(penguinBodyGO);

	Camera::Follow(penguinBodyGO.get());

	backgroundMusic.Play();
}


StageState::~StageState() {
}


void StageState::LoadAssets() {}


void StageState::Update(float dt) {
	auto& inputManager = InputManager::GetInstance();

	quitRequested = inputManager.QuitRequested();
	if (inputManager.IsKeyDown(SDLK_ESCAPE)) {
		popRequested = true;
	}

	Camera::Update(dt);

	UpdateArray(dt);

	for (unsigned i = 0; i < objectArray.size(); i++) {
		auto aCollider = objectArray[i]->GetComponent<Collider>();
		if (aCollider == nullptr) {
			continue;
		}

		for (unsigned j = i + 1; j < objectArray.size(); j++) {
			auto bCollider = objectArray[j]->GetComponent<Collider>();
			if (bCollider == nullptr) {
				continue;
			}

			auto isColliding = Collision::IsColliding(aCollider->box, bCollider->box, Util::DegToRad(objectArray[i]->angleDeg),
			                                          Util::DegToRad(objectArray[j]->angleDeg));

			if (isColliding) {
				objectArray[i]->NotifyCollision(*objectArray[j]);
				objectArray[j]->NotifyCollision(*objectArray[i]);
			}
		}
	}

	if (PenguinBody::player == nullptr) {
		GameData::playerVictory = false;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	} else if (Alien::alienCount == 0) {
		GameData::playerVictory = true;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	}

	// Remove dead objects
	objectArray.erase(
		std::remove_if(objectArray.begin(), objectArray.end(),
		               [](const std::shared_ptr<GameObject>& obj) { return obj->IsDead(); }),
		objectArray.end()
	);
}


void StageState::Render() {
	RenderArray();
}


void StageState::Start() {
	LoadAssets();

	StartArray();

	started = true;
}


void StageState::Pause() {}

void StageState::Resume() {}
