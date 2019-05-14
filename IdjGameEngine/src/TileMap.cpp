#include "pch.h"
#include "TileMap.h"
#include "Camera.h"
#include "Constants.h"


TileMap::TileMap(GameObject& associated, const std::string& file, std::shared_ptr<TileSet>& tileSet):
    Component(associated),
    tileSet(tileSet) {

    Load(file);
}


void TileMap::Load(const std::string& file) {
    std::ifstream fileStream(file);

    if (!fileStream.is_open()) {
        throw std::runtime_error("Can't open file " + file);
    }

    char ignore;
    int tileValue;

    fileStream >> mapWidth >> ignore
        >> mapHeight >> ignore
        >> mapDepth >> ignore;

    while (fileStream >> tileValue >> ignore) {
        tileMatrix.push_back(tileValue - 1);
    }

    auto expectedSize = mapWidth * mapHeight * mapDepth;
    if (tileMatrix.size() != expectedSize) {
        throw std::runtime_error("Invalid tile matrix size");
    }
}


void TileMap::SetTileSet(const std::shared_ptr<TileSet>& tileSet) {
    this->tileSet = tileSet;
}


int& TileMap::At(int x, int y, int z) {
    return tileMatrix.at(x + y * mapWidth + z * mapWidth * mapHeight);
}


void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    auto parallaxOffset = layer * Constants::TileMap::PARALLAX_LAYER_OFFSET;

    for (int i = 0; i < mapWidth; ++i) {
        for (int j = 0; j < mapHeight; ++j) {
            auto tileIndex = At(i, j, layer);
            if (tileIndex != -1) {
                auto x = (i * tileSet->GetTileWidth() - cameraX) - (cameraX * parallaxOffset);
                auto y = (j * tileSet->GetTileHeight() - cameraY) - (cameraY * parallaxOffset);
                tileSet->RenderTile(tileIndex, x, y);
            }
        }
    }
}


int TileMap::GetWidth() const {
    return mapWidth;
}


int TileMap::GetHeight() const {
    return mapHeight;
}


int TileMap::GetDepth() const {
    return mapDepth;
}


void TileMap::Start() {}


void TileMap::Render() {
    for (unsigned i = 0; i < mapDepth; ++i) {
        RenderLayer(i, Camera::pos.x, Camera::pos.y);
    }
}


void TileMap::Update(float dt) {}


ComponentType TileMap::GetType() const {
    return Type;
}
