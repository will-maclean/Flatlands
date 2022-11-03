//
// Created by will on 3/11/22.
//

#pragma once

#include "Entity.h"
#include <string>

class Particle : public Entity {
public:
    Particle(std::string spritePath, olc::vf2d  location, olc::vf2d  velocity, float lifetime);

    bool tick(Game* game, float fElapsedTime) override;

    bool hasChunk() const override {
        return false;
    }
private:
    float lifetime;
    clock_t birthday;
};

