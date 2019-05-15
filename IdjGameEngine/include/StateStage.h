﻿#pragma once
#include "Sprite.h"
#include "Music.h"

class StateStage {
public:
    StateStage();
    ~StateStage();

    void Start();
    void AddObject(const std::shared_ptr<GameObject>& go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
    bool QuitRequested() const;
    void LoadAssets();
    void Update(float dt);
    void Render();

private:
    // Sprite bg;
    Music music;
    bool quitRequested = false;
    bool started = false;
    std::vector<std::shared_ptr<GameObject>> objectArray;
};
