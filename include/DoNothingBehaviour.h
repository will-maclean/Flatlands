//
// Created by Will Maclean on 13/11/2022.
//

#ifndef FLATLANDS_DONOTHINGBEHAVIOUR_H
#define FLATLANDS_DONOTHINGBEHAVIOUR_H

#include "Behaviour.h"

class Game;
class Entity;

class DoNothingBehaviour : public Behaviour {
public:
    bool tick(Entity* entity, Game* game, float fElapsedTime) override;
};


#endif //FLATLANDS_DONOTHINGBEHAVIOUR_H
