#pragma once

#include "Tile.h"
#include "olcPixelGameEngine.h"
#include <vector>

class Chunk{

public:
    Chunk(olc::vi2d anchorLocation);

    ~Chunk();

    void tick(float fElapsedTime);
    void render(class Game* game);

    int getHeight() const {
        return nTilesHeight;
    }

    int getWidth() const {
        return nTilesWidth;
    }

    int getTileWidth() const {
        return mTileWidth;
    }

    int getTileHeight() const {
        return mTileHeight;
    }

    void setTile(Tile* tile, int x, int y){
        this->mTileArr[y][x] = tile;
    }

    Tile* getTile(int x, int y) const{
        return this->mTileArr[y][x];
    }
    
    olc::vf2d getAnchorLocation() const{
        return mAnchorLocation;
    }

    bool contains(olc::vf2d location) const;

    std::vector<Tile *> getCollisionTiles(Entity* entity, olc::vf2d testLocation) const;

private:
    const int nTilesHeight = 64;
    const int nTilesWidth = 16;

    const int mTileWidth = 16;
    const int mTileHeight = 16;

    Tile* mTileArr[64][16];

    // stores the mLocation of the top left of the chunk (locked to integers for easier rendering)
    olc::vi2d mAnchorLocation;

    bool isVisible(Game* game);
    
};
