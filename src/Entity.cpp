#include "Entity.h"
#include "Game.h"
#include "CollisionUtils.h"
#include "CollisionObjects.h"
#include <memory>

Entity::Entity(std::string name, olc::vf2d location, olc::vf2d velocity, float health, std::string spritePath, float width, float height){
    this->name = name;
    this->location = location;
    this->velocity = velocity;
    this->health = health;
    this->width = width;
    this->height = height;

    sprTile = std::make_unique<olc::Sprite>(spritePath);
}

void Entity::render(Game* game){
    game->SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
    game->DrawSprite(location, sprTile.get());
}

void Entity::tick(Game* game, float fElapsedTime){
    // update the position based on the velocity
    if(!touchingGround){
        velocity.y += gravity;
    }

    olc::vf2d testLocation = location + fElapsedTime * velocity;

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
