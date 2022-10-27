#pragma once

#include <string>
#include "olcPixelGameEngine.h"

class Game;

class Entity{
protected:
    std::string name;
    olc::vf2d location;
    olc::vf2d velocity;
    float health;

    std::unique_ptr<olc::Sprite> sprTile;

public:
    Entity(std::string name, olc::vf2d location, olc::vf2d velocity, float health, std::string spritePath);
    
    virtual void tick(Game* game, float fElapsedTime) = 0;
    void render(Game* game);
};