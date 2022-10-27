#pragma once

#include "Entity.h"

class Game;

class Player : public Entity{
private:
    const float MAX_SPEED = 15.0f;
public:
    Player(std::string name, olc::vf2d location);

    void tick(Game* game, float fElapsedTime) override;
};