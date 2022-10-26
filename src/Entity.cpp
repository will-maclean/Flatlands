#include "Entity.h"

Entity::Entity(std::string name, olc::vf2d location, olc::vf2d velocity, float health, std::string spritePath){
    this->name = name;
    this->location = location;
    this->velocity = velocity;
    this->health = health;

    sprTile = std::make_unique<olc::Sprite>(spritePath);
}
