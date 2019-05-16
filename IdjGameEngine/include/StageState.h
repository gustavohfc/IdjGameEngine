#pragma once
#include "Music.h"
#include "State.h"
#include "TileSet.h"

class StageState : public State {
public:
    StageState();
    ~StageState();

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    Music backgroundMusic;
    TileSet* tileSet; // TODO: Why?
};
