//
// Created by will on 10/11/22.
//

#include "Rat.h"
#include <cstdlib>

Rat::Rat(olc::vf2d location)
: Entity("el Rato", location, {0, 0}, 100, "resources/sprites/rat.png", 10, 6){

}

bool Rat::tick(Game* game, float fElapsedTime) {
    // just make a random velocity for now
//    velocity += {static_cast<float>(std::rand() % 10) - 5, static_cast<float>(std::rand() % 10) - 5};

//    if(velocity.mag() > 0){
//        velocity = velocity.norm();
//    }

    return Entity::tick(game, fElapsedTime);
}