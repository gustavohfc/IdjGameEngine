#include "pch.h"
#include "State.h"
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


State::State():
    music("assets/audio/stageState.ogg") {

    auto background = std::make_shared<GameObject>();
    background->AddComponent(std::make_shared<Sprite>(*background, "assets/img/ocean.jpg"));
    background->AddComponent(std::make_shared<CameraFollower>(*background));
    objectArray.push_back(background);

    auto map = std::make_shared<GameObject>();
    auto tileSet = std::make_shared<TileSet>(*map, Constants::TileSet::TILE_WIDTH, Constants::TileSet::TILE_HEIGHT, "assets/img/tileset.png");
    auto tileMap = std::make_shared<TileMap>(*map, "assets/map/tileMap.txt", tileSet);

    // TODO: why set to (0, 0)?
    map->box.x = 0;
    map->box.y = 0;
    //map->box.w = tileMap->GetWidth() * 64;
    //map->box.h = tileMap->GetHeight() * 64;

    map->AddComponent(tileMap);
    objectArray.push_back(map);

    auto alienGO = std::make_shared<GameObject>();
    alienGO->AddComponent(std::make_shared<Alien>(*alienGO, Constants::Alien::NUMBER_OF_MINIONS));
    alienGO->box.SetCenter(Constants::Alien::INITIAL_POSITION_X, Constants::Alien::INITIAL_POSITION_Y);
    objectArray.push_back(alienGO);

    auto penguinBodyGO = std::make_shared<GameObject>();
    penguinBodyGO->AddComponent(std::make_shared<PenguinBody>(*penguinBodyGO));
    penguinBodyGO->box.SetCenter(Constants::PenguinBody::INITIAL_POSITION_X, Constants::PenguinBody::INITIAL_POSITION_Y);
    objectArray.push_back(penguinBodyGO);

    Camera::Follow(penguinBodyGO.get());

    music.Play();
}


State::~State() {
    objectArray.clear();
}


void State::Start() {
    LoadAssets();

    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }

    started = true;
}


void State::AddObject(const std::shared_ptr<GameObject>& go) {
    objectArray.push_back(go);

    if (started) {
        go->Start();
    }
}


std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (int i = 0; i < objectArray.size(); ++i) {
        if (go == objectArray[i].get()) {
            return objectArray[i];
        }
    }

    return std::weak_ptr<GameObject>();
}


bool State::QuitRequested() const {
    return quitRequested;
}


void State::LoadAssets() {}


void State::Update(float dt) {
    auto& inputManager = InputManager::GetInstance();

    quitRequested = inputManager.QuitRequested();

    Camera::Update(dt);

    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for (int i = 0; i < objectArray.size(); i++) {
        auto aCollider = objectArray[i]->GetComponent<Collider>();
        if (aCollider == nullptr) {
            continue;
        }

        for (int j = i + 1; j < objectArray.size(); j++) {
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

    // Remove dead objects
    objectArray.erase(
        std::remove_if(objectArray.begin(), objectArray.end(),
                       [](const std::shared_ptr<GameObject>& obj) { return obj->IsDead(); }),
        objectArray.end()
    );
}


void State::Render() {
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}
