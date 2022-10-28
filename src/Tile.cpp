#include "Tile.h"
#include "Game.h"
#include <stdlib.h>
#include "Entity.h"

Tile::Tile(olc::vf2d anchorLocation, std::string spritePath, bool randomFlip, bool mIsSolid){
    this->mIsSolid = mIsSolid;
    this->anchorLocation = anchorLocation;
    
    sprTile = std::make_unique<olc::Sprite>(spritePath);

    if(randomFlip){
        int flipType = rand() % 3;

        flip = olc::Sprite::Flip(flipType);
    }else{
        flip = olc::Sprite::Flip(0);
    }
}

Tile::Tile(olc::vf2d anchorLocation, bool mIsSolid){
    this->anchorLocation = anchorLocation;
    this->mIsSolid = mIsSolid;
    sprTile = nullptr;
}

void Tile::tick(float fElapsedTime){
    //do nothing for now
}

void Tile::render(Game* game, olc::vi2d location){
    // just render the sprite, if defined
    if(sprTile != nullptr){
        game->DrawSprite(location, sprTile.get(), 1, flip);
        // game->DrawSprite()
    }
}

bool Tile::entityCollision(Entity* entity){
    return ((entity->getLocation().x < anchorLocation.x + getTileWidth()) 
                && (anchorLocation.x < entity->getLocation().x + entity->getWidth()))
                && ((entity->getLocation().y < anchorLocation.y + getTileHeight()) 
                && (anchorLocation.y < entity->getLocation().y + entity->getHeight()));
            
}

EmptyTile::EmptyTile(olc::vf2d anchorLocation)
    : Tile(anchorLocation, false){
}

DirtTile::DirtTile(olc::vf2d anchorLocation)
    : Tile(anchorLocation, "./resources/sprites/pixel_dirt.png", true, true){

    }

GrassyDirtTile::GrassyDirtTile(olc::vf2d anchorLocation)
    : Tile(anchorLocation, "./resources/sprites/pixel_grassy_dirt.png", false, true){

    }
