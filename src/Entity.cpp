#include "Entity.h"
#include "Game.h"
#include "CollisionUtils.h"
#include "CollisionObjects.h"
#include "MathUtils.h"
#include <memory>
#include <iostream>

Entity::Entity(std::string name, olc::vf2d location, olc::vf2d velocity, float health, std::string spritePath, float width, float height){
    this->name = name;
    this->location = location;
    this->velocity = velocity;
    this->health = health;
    this->width = width;
    this->height = height;
    movingRight = false;
    currChunk = nullptr;

    sprTile = std::make_unique<olc::Sprite>(spritePath);
    scaling = {width / sprTile->width, height / sprTile->height};
    decalTile = std::make_unique<olc::Decal>(sprTile.get());
}

void Entity::render(Game* game){
    game->SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
    olc::vf2d drawPos = location - game->getRenderOffset();

    olc::vf2d drawScaling = {1, 1};
//    if(velocity.x > 0){
//        // facing right!
//        drawScaling.x *= -1;
//        drawPos.x += width;
//    }
//    std::cout << drawPos << std::endl;
    game->DrawDecal(drawPos, decalTile.get(), drawScaling);
}

bool Entity::tick(Game* game, float fElapsedTime){
    if(movingRight){
        if (velocity.x < 0){
            movingRight = false;
        }
    }else{
        if (velocity.x > 0){
            movingRight = true;
        }
    }

    // update the position based on the velocity
    if(!touchingGround){
        velocity.y += fElapsedTime * gravity;
    }

    olc::vf2d dummyLocation = location + fElapsedTime * velocity;

    olc::vf2d testLocation = {dummyLocation.x, clip(dummyLocation.y, game->getWorldMin(), game->getWorldMax())};

    std::vector<Tile *> collisionTiles = currChunk->getCollisionTiles(this, testLocation);

    olc::vf2d newLocation;

    if(collisionTiles.empty()){
        // no collisions! beauty
        newLocation = testLocation;
    }else{
        // collision! we'll have to sort this out.

        // easiest solution is to just not move the entity
        newLocation = getNewLocation(collisionTiles, this, game->getTouchThreshold(), testLocation, location);
        velocity.y = 0;  // if there's a collision, stop moving
    }

    location = newLocation;

    // now that we've set the location of the entity, check if we're touching the
    // ground
    detectTouchingGround(game->getTouchThreshold());

    if(touchingGround){
        canJump = true;
        touchingGround = true;
    }

    return true;
}

void Entity::detectTouchingGround(float touchThreshold){
    //TODO: why does this feel so janky in so many ways?

    // check if we're close enough to the ground to be called "touching"

    // just check all the tiles for now because I'm lazy and can't be bothered optimising
    for(int i = 0; i < currChunk->getWidth(); i++){
        for(int j = 0; j < currChunk->getHeight(); j++){
            Tile* currTile = currChunk->getTile(j, i);

            if(currTile->entityStandingOn(this, touchThreshold)){
                touchingGround = true;
                canJump = true;
                return;
            }
        }
    }

    touchingGround = false;
    canJump = false;
}

std::unique_ptr<Rectangle> Entity::getRectangle(){
    return std::unique_ptr<Rectangle>(new Rectangle(location, width, height)); 
}
