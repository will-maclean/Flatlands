#include "Entity.h"

Entity::Entity(std::string name, olc::vf2d location, olc::vf2d velocity, float health){
    this->name = name;
    this->location = location;
    this->velocity = velocity;
    this->health = health;
}

// Entity::Entity(){
//     this->name = "TestName";
//     this->location = {0.0f, 0.0f};
//     this->velocity = {0.0f, 0.0f};
//     this->health = 100;
// }