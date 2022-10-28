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
    // render all the tiles
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


std::vector<Tile *> Chunk::getCollisionTiles(Entity* entity) const{
    // For now, just testing point collision, rather than solid collision
    
    std::vector<Tile *> collisionTiles;

    if(!contains(entity->getLocation())){
        // if the location isn't even in the chunk,
        // then obviously there are no collisions
       return collisionTiles;
    }

    std::cout << "Entity Location: " << entity->getLocation() << std::endl;
    
    // loop through all of the tiles (could optimise later?)
    for(int i = 0; i < nTilesHeight; i++){
        for(int j = 0; j < nTilesWidth; j++){
            Tile* locationTile = getTile(j, i);

            // if the entity is colliding with the tile, and the tile is solid, add it to 
            // the vector of collision tiles
            if (locationTile->entityCollision(entity) && locationTile->isSolid()){
                std::cout << "collision with tile at " << locationTile->getAnchorLocation() << std::endl;
                collisionTiles.push_back(locationTile);
            }
        }
    }

    return collisionTiles;
}
