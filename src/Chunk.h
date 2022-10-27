#pragma once

#include "Tile.h"
#include "olcPixelGameEngine.h"
#include <vector>

class Chunk{
private:
    const int nTilesHeight = 64;
    const int nTilesWidth = 16;

    const int tileWidth = 16;
    const int tileHeight = 16;

    Tile* tileArr[64][16];

    // stores the location of the top left of the chunk (locked to integers for easier rendering)
    olc::vi2d anchorLocation;

public:
    Chunk(olc::vi2d anchorLocation);

    void tick(float fElapsedTime);
    void render(class Game* game);

    int getHeight() const {
        return nTilesHeight;
    }

    int getWidth() const {
        return nTilesWidth;
    }

    void setTile(Tile* tile, int x, int y){
        this->tileArr[y][x] = tile;
    }

    Tile* getTile(int x, int y) const{
        return this->tileArr[y][x];
    }

    bool contains(olc::vf2d location) const;

    std::vector<Tile *> getCollisionTiles(olc::vf2d testLocation) const;

    
};