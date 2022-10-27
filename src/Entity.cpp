#include "Entity.h"
#include "Game.h"

Entity::Entity(std::string name, olc::vf2d location, olc::vf2d velocity, float health, std::string spritePath){
    this->name = name;
    this->location = location;
    this->velocity = velocity;
    this->health = health;

    sprTile = std::make_unique<olc::Sprite>(spritePath);
}

void Entity::render(Game* game){
    game->SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
    game->DrawSprite(location, sprTile.get());
}

// void Entity::tick(Game* game, float fElapsedTime){
//     // update the position based on the velocity
//     location = location + fElapsedTime * velocity;
// }