#pragma once
#include "Sprite.h"
#include "Music.h"

class State {
public:
    State();
    ~State();

    bool QuitRequested() const;
    void LoadAssets();
    void Update(float dt);
    void Render();

private:
    // Sprite bg;
    Music music;
    bool quitRequested = false;
    std::vector<std::unique_ptr<GameObject>> objectArray;

    void Input();
    void AddObject(int mouseX, int mouseY);
};
