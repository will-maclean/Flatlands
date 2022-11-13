//
// Created by Will Maclean on 13/11/2022.
//
#include "RandomMovementBehaviour.h"
#include "Entity.h"
#include <cstdlib>

RandomMovementBehaviour::RandomMovementBehaviour(float xMin, float xMax, float yMin, float yMax, float updateEvery) {
    mUpdateEvery = updateEvery;
    mCurrTimer = 0;

    mXMin = xMin;
    mXMax = xMax;
    mYMin = yMin;
    mYMax = yMax;
}


bool RandomMovementBehaviour::tick(Entity* entity, Game *game, float fElapsedTime) {
    mCurrTimer += fElapsedTime;

    if(mCurrTimer >= mUpdateEvery){
        mCurrTimer = 0;

        float x = (mXMax - mXMin)*((std::rand() % 100) / 100.0f) + mXMin;
        float y = (mYMax - mYMin)*((std::rand() % 100) / 100.0f) + mYMin;

        entity->setVelocity({x, y});
    }
    return true;
}