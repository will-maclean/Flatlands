#include "Chunk.h"
#include "TileInitStrategy.h"
#include "Game.h"

Chunk::Chunk(olc::vi2d anchorLocation){
    this->anchorLocation = anchorLocation;

    // init the tiles
    defaultTileInitStrategy(this);
}

void Chunk::tick(float fElapsedTime){
    // tick all the tiles
    for(int i = 0; i < nTilesHeight; i++){
        for(int j = 0; j < nTilesWidth; j++){
            tileArr[i][j]->tick(fElapsedTime);
        }
    }
}

void Chunk::render(Game* game){
    // tick all the tiles
    for(int i = 0; i < nTilesHeight; i++){
        for(int j = 0; j < nTilesWidth; j++){
            tileArr[i][j]->render(game, {anchorLocation.x + j * tileWidth, anchorLocation.y + i * tileHeight});
        }
    }
}

bool Chunk::contains(olc::vf2d location) const{
    // although we currently assume chunks span the 
    // entirety of the world in the vertical direction,
    // we'll still check the y coords in case this 
    // assumption changes in the future
    float xMin = anchorLocation.x;
    float xMax = anchorLocation.y + nTilesWidth * tileWidth;
    float yMin = anchorLocation.x ;
    float yMax = anchorLocation.y + nTilesHeight * tileHeight;

    return (xMin <= location.x) && (location.x <= xMax) && (yMin <= location.y) && (location.y <= yMax);
}

std::vector<Tile *> Chunk::getCollisionTiles(olc::vf2d testLocation) const{
    // For now, just testing point collision, rather than solid collision
    
    std::vector<Tile *> collisionTiles;

    if(!contains(testLocation)){
        // if the location isn't even in the chunk,
        // then obviously there are no collisions
        return collisionTiles;
    }

    // the location is inside the chunk. Get the tile at the 
    // chunk's location and see if it is solid or not
    int xIdx = (testLocation.x - anchorLocation.x) / tileWidth;
    int yIdx = (testLocation.y - anchorLocation.y) / tileHeight;

    Tile* locationTile = getTile(xIdx, yIdx);

    if (locationTile->isSolid()){
        collisionTiles.push_back(locationTile);
    }

    return collisionTiles;
}