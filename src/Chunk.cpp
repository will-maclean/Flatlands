#include "Chunk.h"
#include "TileInitStrategy.h"
#include "Game.h"

Chunk::Chunk(olc::vi2d anchorLocation){
    this->mAnchorLocation = anchorLocation;

    // init the tiles
    defaultTileInitStrategy(this);
}

Chunk::~Chunk(){
    for(int i = 0; i < nTilesHeight; i++){
        for(int j = 0; j < nTilesWidth; j++){
            if(mTileArr[i][j]){
                delete mTileArr[i][j];
            }
        }
    }
}

void Chunk::tick(float fElapsedTime){
    // tick all the tiles
    for(int i = 0; i < nTilesHeight; i++){
        for(int j = 0; j < nTilesWidth; j++){
            mTileArr[i][j]->tick(fElapsedTime);
        }
    }
}

void Chunk::render(Game* game){
    if(!isVisible(game)){
        return;
    }
    // render all the tiles
    for(int i = 0; i < nTilesHeight; i++){
        for(int j = 0; j < nTilesWidth; j++){
            mTileArr[i][j]->render(game, {mAnchorLocation.x + j * mTileWidth, mAnchorLocation.y + i * mTileHeight});
        }
    }
}

bool Chunk::contains(olc::vf2d location) const{
    // although we currently assume mChunks span the
    // entirety of the world in the vertical direction,
    // we'll still check the y coords in case this 
    // assumption changes in the future
    float xMin = mAnchorLocation.x;
    float xMax = mAnchorLocation.x + nTilesWidth * mTileWidth;
    float yMin = mAnchorLocation.y ;
    float yMax = mAnchorLocation.y + nTilesHeight * mTileHeight;

    return (xMin <= location.x) && (location.x <= xMax) && (yMin <= location.y) && (location.y <= yMax);
}


std::vector<Tile *> Chunk::getCollisionTiles(Entity* entity, olc::vf2d testLocation) const{
    // For now, just testing point collision, rather than solid collision
    
    std::vector<Tile *> collisionTiles;

    if(!contains(testLocation)){
        // if the mLocation isn't even in the chunk,
        // then obviously there are no collisions
       return collisionTiles;
    }

    // std::cout << "Entity Location: " << entity->getLocation() << std::endl;
    
    // loop through all of the tiles (could optimise later?)
    for(int i = 0; i < nTilesHeight; i++){
        for(int j = 0; j < nTilesWidth; j++){
            Tile* locationTile = getTile(j, i);

            // if the entity is colliding with the tile, and the tile is solid, add it to 
            // the vector of collision tiles
            if (locationTile->entityCollision(entity, testLocation) && locationTile->isSolid()){
                // std::cout << "collision with tile at " << locationTile->getAnchorLocation() << std::endl;
                collisionTiles.push_back(locationTile);
            }
        }
    }

    return collisionTiles;
}

bool Chunk::isVisible(Game* game){
    auto gameScreenRect = game->getScreenRect();

    return gameScreenRect->collision(std::make_unique<Rectangle>(mAnchorLocation, mTileWidth * nTilesWidth, mTileHeight * nTilesHeight));
}