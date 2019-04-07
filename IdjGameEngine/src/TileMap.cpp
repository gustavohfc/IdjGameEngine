#include "pch.h"
#include "TileMap.h"


TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet):
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


void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet = tileSet;
}


int& TileMap::At(int x, int y, int z) {
    return tileMatrix.at(x + y * mapWidth + z * mapWidth * mapHeight);
}


void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (int x = 0; x < mapWidth; ++x) {
        for (int y = 0; y < mapHeight; ++y) {
            auto tileIndex = At(x, y, layer);
            if (tileIndex != -1) {
                tileSet->RenderTile(At(x, y, layer), x, y);
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


void TileMap::Render() {
    for (unsigned i = 0; i < mapDepth; ++i) {
        RenderLayer(i);
    }
}


void TileMap::Update(float dt) {}


bool TileMap::Is(const std::string& type) {
    return type == "TileMap";
}
