#pragma once

#include "Entity.h"

class Game;

class Player : public Entity{
private:
    const float MAX_SPEED = 15.0f;
    const float JUMP_VEL = 20;
    olc::vf2d inputVel;
public:
    Player(std::string name, olc::vf2d location);

    void tick(Game* game, float fElapsedTime) override;
};