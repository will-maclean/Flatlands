//
// Created by will on 3/11/22.
//

#include "Particle.h"
#include <string>
#include <iostream>

Particle::Particle(std::string spritePath, olc::vf2d  location, olc::vf2d  velocity, float lifetime)
        : Entity("particle", location, velocity, 1, spritePath, 8, 8){
    std::cout << spritePath << std::endl;
    this->lifetime = lifetime;
    this->birthday = std::clock();
}

bool Particle::tick(Game* game, float fElapsedTime) {
    velocity.y += 3 * fElapsedTime * gravity;

    location = location + fElapsedTime * velocity;

    return std::clock() - birthday > lifetime;
}