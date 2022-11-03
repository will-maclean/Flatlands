#include "GlitterParticle.h"
#include "Particle.h"
#include <string>
#include <stdlib.h>

GlitterParticle::GlitterParticle(olc::vf2d  location, olc::vf2d  velocity, float lifetime)
    : Particle("resources/sprites/glitter" + std::to_string(std::rand() % 5 + 1) + ".png", location, velocity, lifetime){
}