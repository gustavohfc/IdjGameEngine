#include "pch.h"
#include "TileSet.h"


TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, const std::string& file):
    tileSet(associated, file),
    tileWidth(tileWidth),
    tileHeight(tileHeight) {

    rows = tileSet.GetHeight() / tileWidth;
    columns = tileSet.GetWidth() / tileHeight;
}


void TileSet::RenderTile(unsigned index, float x, float y) {
    if (index > (rows * columns) - 1) {
        throw std::logic_error("Trying to access a invalid tile, index = " + std::to_string(index));
    }

    auto tileX = (index % columns) * tileWidth;
    auto tileY = (index / columns) * tileHeight;
    tileSet.SetClip(tileX, tileY, tileWidth, tileHeight);

    tileSet.Render(x * tileWidth, y * tileHeight, tileWidth, tileHeight);
}


int TileSet::GetTileWidth() const {
    return tileWidth;
}


int TileSet::GetTileHeight() const {
    return tileHeight;
}
