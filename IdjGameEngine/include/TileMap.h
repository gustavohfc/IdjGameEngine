﻿#pragma once
#include "Component.h"
#include "TileSet.h"

class TileMap : public Component {
public:
    TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);

    void Load(const std::string& file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z);
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
    int GetWidth();
    int GetHeight();
    int GetDepth();

    void Render() override;
    void Update(float dt) override;
    bool Is(const std::string& type) override;

private:
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    unsigned mapWidth, mapHeight, mapDepth;
};