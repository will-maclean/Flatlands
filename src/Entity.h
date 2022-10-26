#pragma once

#include <string>
#include "olcPixelGameEngine.h"

class Entity{
private:
    std::string name;
    olc::vf2d location;
    olc::vf2d velocity;
    float health;

public:
    Entity(std::string name, olc::vf2d location, olc::vf2d velocity, float health);
    Entity(){
        this->name = "TestName";
        this->location = {0.0f, 0.0f};
        this->velocity = {0.0f, 0.0f};
        this->health = 100;
    }
    
    virtual void tick(float fElapsedTime) = 0;
    virtual void render(class Game* game) = 0;
};