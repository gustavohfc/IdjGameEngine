#include "pch.h"
#include "State.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"


State::State():
    music("assets/audio/stageState.ogg") {

    auto background = std::make_shared<GameObject>();
    background->AddComponent(std::make_shared<Sprite>(*background, "assets/img/ocean.jpg"));
    background->AddComponent(std::make_shared<CameraFollower>(*background));
    objectArray.push_back(background);

    auto map = std::make_shared<GameObject>();
    auto tileSet = std::make_shared<TileSet>(*map, 64, 64, "assets/img/tileset.png");
    auto tileMap = std::make_shared<TileMap>(*map, "assets/map/tileMap.txt", tileSet);

    // TODO: why set to (0, 0)?
    map->box.x = 0;
    map->box.y = 0;
    //map->box.w = tileMap->GetWidth() * 64;
    //map->box.h = tileMap->GetHeight() * 64;

    map->AddComponent(tileMap);
    objectArray.push_back(map);

    auto alien = std::make_shared<GameObject>();
    alien->AddComponent(std::make_shared<Alien>(*alien, 5));
    alien->box.SetCenter(512, 300);
    objectArray.push_back(alien);


    auto penguinBody = std::make_shared<GameObject>();
    penguinBody->AddComponent(std::make_shared<PenguinBody>(*penguinBody));
    penguinBody->box.SetCenter(704, 640);
    objectArray.push_back(penguinBody);

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
    for (auto&& gameObject : objectArray) {
        if (go == gameObject.get()) {
            return gameObject;
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
