//
// Created by Will Maclean on 13/11/2022.
//

#pragma once

#include "Behaviour.h"

class Game;
class Entity;

class RandomMovementBehaviour : public Behaviour {
public:
    explicit RandomMovementBehaviour(float xMin, float xMax, float yMin, float yMax, float updateEvery);

    bool tick(Entity* entity, Game* game, float fElapsedTime) override;

private:
    float mUpdateEvery, mCurrTimer;

    float mXMin, mXMax, mYMin, mYMax;
};
