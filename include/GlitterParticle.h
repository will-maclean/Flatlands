//
// Created by will on 2/11/22.
//

#pragma once

#include "Particle.h"
#include <ctime>

class Game;

class GlitterParticle : public Particle{
public:
    GlitterParticle(olc::vf2d  location, olc::vf2d  velocity, float lifetime);
};
