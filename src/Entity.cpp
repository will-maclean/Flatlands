#include "Entity.h"
#include "Game.h"
#include "CollisionUtils.h"
#include "CollisionObjects.h"
#include "MathUtils.h"
#include <memory>
#include <iostream>

Entity::Entity(std::string name, olc::vf2d location, olc::vf2d velocity, float health, std::string spritePath, float width, float height){
    this->mName = name;
    this->mLocation = location;
    this->mVelocity = velocity;
    this->mHealth = health;
    this->mWidth = width;
    this->mHeight = height;
    mMovingRight = false;
    mCurrChunk = nullptr;

    mSprTile = std::make_unique<olc::Sprite>(spritePath);
    mScaling = {width / mSprTile->width, height / mSprTile->height};
    mDecalTile = std::make_unique<olc::Decal>(mSprTile.get());
}

void Entity::render(Game* game){
    game->SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
    olc::vf2d drawPos = mLocation - game->getRenderOffset();

    olc::vf2d drawScaling = mScaling;

    if(mMovingRight){
        // facing right!
        drawScaling.x *= -1;
        drawPos.x += mWidth;
    }
//    std::cout << drawPos << std::endl;
    game->DrawDecal(drawPos, mDecalTile.get(), drawScaling);
}

bool Entity::tick(Game* game, float fElapsedTime){
    if(mMovingRight){
        if (mVelocity.x < 0){
            mMovingRight = false;
        }
    }else{
        if (mVelocity.x > 0){
            mMovingRight = true;
        }
    }

    // update the position based on the mVelocity
    if(!mTouchingGround){
        mVelocity.y += fElapsedTime * mGravity;
    }

    olc::vf2d dummyLocation = mLocation + fElapsedTime * mVelocity;

    olc::vf2d testLocation = {dummyLocation.x, clip(dummyLocation.y, game->getWorldMin(), game->getWorldMax())};

    std::vector<Tile *> collisionTiles = mCurrChunk->getCollisionTiles(this, testLocation);

    olc::vf2d newLocation;

    if(collisionTiles.empty()){
        // no collisions! beauty
        newLocation = testLocation;
    }else{
        // collision! we'll have to sort this out.

        // easiest solution is to just not move the entity
        newLocation = getNewLocation(collisionTiles, this, game->getTouchThreshold(), testLocation, mLocation);
        mVelocity.y = 0;  // if there's a collision, stop moving
    }

    mLocation = newLocation;

    // now that we've set the mLocation of the entity, check if we're touching the
    // ground
    detectTouchingGround(game->getTouchThreshold());

    if(mTouchingGround){
        mCanJump = true;
        mTouchingGround = true;
    }

    return true;
}

void Entity::detectTouchingGround(float touchThreshold){
    //TODO: why does this feel so janky in so many ways?

    // check if we're close enough to the ground to be called "touching"

    // just check all the tiles for now because I'm lazy and can't be bothered optimising
    for(int i = 0; i < mCurrChunk->getWidth(); i++){
        for(int j = 0; j < mCurrChunk->getHeight(); j++){
            Tile* currTile = mCurrChunk->getTile(j, i);

            if(currTile->entityStandingOn(this, touchThreshold)){
                mTouchingGround = true;
                mCanJump = true;
                return;
            }
        }
    }

    mTouchingGround = false;
    mCanJump = false;
}

std::unique_ptr<Rectangle> Entity::getRectangle(){
    return std::unique_ptr<Rectangle>(new Rectangle(mLocation, mWidth, mHeight));
}
