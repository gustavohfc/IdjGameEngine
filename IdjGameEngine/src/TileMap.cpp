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
    auto index = x + y * mapWidth + z * mapWidth * mapHeight;
    return tileMatrix.at(index);
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return  mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}

void TileMap::Render() {}

void TileMap::Update(float dt) {}


bool TileMap::Is(const std::string& type) {
    // TODO
    return false;
}
