//
// Created by will on 10/11/22.
//

#include "Rat.h"
#include "BehaviourEntity.h"
#include "RandomMovementBehaviour.h"

Rat::Rat(olc::vf2d location)
: BehaviourEntity("el Rato", location, {0, 0}, 100, "resources/sprites/rat.png", 10, 6){
    setCurrBehaviour(new RandomMovementBehaviour(-5, 5, 0, 0, 5));
}