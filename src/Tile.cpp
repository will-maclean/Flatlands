#include "Tile.h"
#include "Game.h"
#include <memory>
#include "Entity.h"

Tile::Tile(olc::vf2d anchorLocation, std::string spritePath, bool randomFlip, bool mIsSolid)
    : Rectangle(anchorLocation, 16, 16){
    this->mIsSolid = mIsSolid;
    this->mAnchorLocation = anchorLocation;

    mSprFragment = std::make_unique<olc::Sprite>(spritePath);

    // Create decal of fragment
    mDecalTile = std::make_unique<olc::Decal>(mSprFragment.get());

    if(randomFlip){
        int flipType = rand() % 4;

        mDecalRotate = flipType * 1.5708; // 1.5708 = 90 degrees in radians
    }else{
        mDecalRotate = 0;
    }
}

Tile::Tile(olc::vf2d anchorLocation, bool mIsSolid)
    : Rectangle(anchorLocation, 16, 16){
    this->mAnchorLocation = anchorLocation;
    this->mIsSolid = mIsSolid;
    mDecalTile = nullptr;
}

void Tile::tick(float fElapsedTime){
    //do nothing for now
}

void Tile::render(Game* game, olc::vi2d location){
    //TODO: do we want to check whether individual tiles are visible before rendering? Currently we check whether a
    // a chunk is visible, and if so render all tiles inside it.

    // just render the sprite, if defined
    if(mDecalTile){
        olc::vf2d offsetLoc = {8, 8};
        game->DrawRotatedDecal(location + offsetLoc - game->getRenderOffset(), mDecalTile.get(), mDecalRotate, offsetLoc);
        // game->DrawSprite()
    }
}

bool Tile::entityCollision(Entity* entity, olc::vf2d testLocation){
    return Rectangle::collision(std::unique_ptr<Rectangle>(new Rectangle(testLocation, entity->getWidth(), entity->getHeight())));
}

bool Tile::entityStandingOn(Entity* entity, float touchThreshold){
    std::unique_ptr<Rectangle> entityRect = entity->getRectangle();
    std::shared_ptr<Rectangle> touchRect = std::shared_ptr<Rectangle>(new Rectangle({mAnchorLocation.x, mAnchorLocation.y - touchThreshold}, getTileWidth(), touchThreshold));
    return entityRect->collision(touchRect) && mIsSolid;
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
