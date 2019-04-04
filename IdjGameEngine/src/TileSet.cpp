#include "pch.h"
#include "TileSet.h"


TileSet::TileSet(int tileWidth, int tileHeight, const std::string& file):
    // TODO GameObject
    tileSet(*(new GameObject), file),
    tileWidth(tileWidth),
    tileHeight(tileHeight) {
    
    rows = tileSet.GetHeight() / tileWidth;
    columns = tileSet.GetWidth() / tileHeight;
}


void TileSet::RenderTile(unsigned index, float x, float y) {
    // TODO: validate index

    // TODO: call sprite render
}

int TileSet::GetTileWidth() const {
    return tileWidth;
}

int TileSet::GetTileHeight() const {
    return tileHeight;
}
