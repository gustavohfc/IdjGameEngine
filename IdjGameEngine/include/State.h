#pragma once
#include "Sprite.h"
#include "Music.h"
#include "Game.h"

class State {
public:
    State();
    ~State();

    void Start();
    void AddObject(const std::shared_ptr<GameObject>& go);
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

    void AddObject(int mouseX, int mouseY);
};
