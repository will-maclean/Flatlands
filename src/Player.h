#pragma once

#include "Entity.h"


class Player : public Entity{
public:
    // Player(std::string name, olc::vf2d location);
    // Player(std::string name);
    Player();

    void tick(float fElapsedTime) override;

    void render(class Game* game) override;
};