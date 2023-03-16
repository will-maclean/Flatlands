//
// Created by Will Maclean on 13/11/2022.
//

#pragma once

#include "Behaviour.h"

class Game;
class Entity;

class DoNothingBehaviour : public Behaviour {
public:
    bool tick(Entity* entity, Game* game, float fElapsedTime) override;
};
