#pragma once

#include "Entity.h"

class Game;

class Player : public Entity{
public:
    Player(std::string name, olc::vf2d location);

    void tick(float fElapsedTime) override;

    void render(Game* game) override;
};