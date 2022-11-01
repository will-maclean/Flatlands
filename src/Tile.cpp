#include "Tile.h"
#include "Game.h"
#include <stdlib.h>
#include <memory>
#include <iostream>
#include "Entity.h"

Tile::Tile(olc::vf2d anchorLocation, std::string spritePath, bool randomFlip, bool mIsSolid)
    : Rectangle(anchorLocation, 16, 16){
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

Tile::Tile(olc::vf2d anchorLocation, bool mIsSolid)
    : Rectangle(anchorLocation, 16, 16){
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

bool Tile::entityCollision(Entity* entity, olc::vf2d testLocation){
    return Rectangle::collision(std::unique_ptr<Rectangle>(new Rectangle(testLocation, entity->getWidth(), entity->getHeight())));
}

bool Tile::entityStandingOn(Entity* entity, float touchThreshold){
    std::unique_ptr<Rectangle> entityRect = entity->getRectangle();
    std::shared_ptr<Rectangle> touchRect = std::shared_ptr<Rectangle>(new Rectangle({anchorLocation.x, anchorLocation.y - touchThreshold}, getTileWidth(), touchThreshold));
    bool standing =  entityRect->collision(touchRect) && mIsSolid;

    if (standing){
        std::cout << "Player at " << entity->getLocation() << std::endl;
        std::cout << "Standing on block at " << anchorLocation << std::endl;
        std::cout << "Entity rectange anchor: " << entityRect->getAnchorLocation() << ", width: " << entityRect->getWidth() << ", height: " << entityRect->getHeight() << std::endl;
        std::cout << "Tile rectange anchor: " << touchRect->getAnchorLocation() << ", width: " << touchRect->getWidth() << ", height: " << touchRect->getHeight() << std::endl;
    }

    return standing;
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
