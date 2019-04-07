#pragma once
#include "Component.h"
#include "TileSet.h"

class TileMap : public Component {
public:
    TileMap(GameObject& associated, const std::string& file, std::shared_ptr<TileSet>& tileSet);

    void Load(const std::string& file);
    void SetTileSet(const std::shared_ptr<TileSet>& tileSet);
    int& At(int x, int y, int z);
    void RenderLayer(int layer, int cameraX, int cameraY);
    int GetWidth() const;
    int GetHeight() const;
    int GetDepth() const;

    void Render() override;
    void Update(float dt) override;
    bool Is(const std::string& type) override;

private:
    std::vector<int> tileMatrix;
    std::shared_ptr<TileSet> tileSet;
    unsigned mapWidth, mapHeight, mapDepth;
};
