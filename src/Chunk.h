#pragma once

#include "Tile.h"
#include "olcPixelGameEngine.h"

class Chunk{
private:
    const int height = 64;
    const int width = 16;

    const int tileRenderWidth = 16;
    const int tileRenderHeight = 16;

    Tile* tileArr[64][16];

    // stores the location of the top left of the chunk (locked to integers for easier rendering)
    olc::vi2d anchorLocation;

public:
    Chunk(olc::vi2d anchorLocation);

    void tick(float fElapsedTime);
    void render(class Game* game);

    int getHeight() const {
        return height;
    }

    int getWidth() const {
        return width;
    }

    void setTile(Tile* tile, int x, int y){
        this->tileArr[y][x] = tile;
    }

    Tile* getTile(int x, int y) const{
        return this->tileArr[y][x];
    }
};