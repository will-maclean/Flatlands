//
// Created by will on 3/11/22.
//

#include "Particle.h"
#include <string>

Particle::Particle(std::string spritePath, olc::vf2d  location, olc::vf2d  velocity, float lifetime)
        : Entity("particle", location, velocity, 1, spritePath, 8, 8){
    this->mLifetime = lifetime;
    this->mBirthday = std::clock();
}

bool Particle::tick(Game* game, float fElapsedTime) {
    mVelocity.y += 3 * fElapsedTime * mGravity;

    mLocation = mLocation + fElapsedTime * mVelocity;

    return std::clock() - mBirthday > mLifetime;
}