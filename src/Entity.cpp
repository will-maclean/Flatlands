#include "Entity.h"
#include "Game.h"
#include "CollisionUtils.h"
#include <iostream>

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
    velocity.y += gravity;

    olc::vf2d testLocation = location + fElapsedTime * velocity;

    std::vector<Tile *> collisionTiles = currChunk->getCollisionTiles(this);

    olc::vf2d newLocation;

    if(collisionTiles.size() == 0){
        // no collisions! beauty
        newLocation = testLocation;
    }else{
        // collision! we'll have to sort this out.

        // easiest solution is to just not move the entity
        newLocation = getNewLocation(collisionTiles, this, game->getTouchThreshold(), testLocation, location);

    }

    location = newLocation;
}
