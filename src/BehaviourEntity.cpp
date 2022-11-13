//
// Created by Will Maclean on 13/11/2022.
//
#include "BehaviourEntity.h"
#include "Behaviour.h"
#include "DoNothingBehaviour.h"

#include <string>

BehaviourEntity::BehaviourEntity(std::string name, olc::vf2d location, olc::vf2d velocity, float health, std::string spritePath, float width, float height)
    : Entity(name, location, velocity, health, spritePath, width, height)
{
    mCurrBehaviour = new DoNothingBehaviour();
}

BehaviourEntity::~BehaviourEntity(){
    delete mCurrBehaviour;
}

bool BehaviourEntity::tick(Game *game, float fElapsedTime) {
    bool result = mCurrBehaviour->tick(this, game, fElapsedTime);

    Entity::tick(game, fElapsedTime);

    return result;
}

void BehaviourEntity::setCurrBehaviour(Behaviour *behaviour) {
    // may have been heap allocated - delete first
    delete mCurrBehaviour;
    mCurrBehaviour = behaviour;
}