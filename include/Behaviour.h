//
// Created by Will Maclean on 13/11/2022.
//

#ifndef FLATLANDS_BEHAVIOUR_H
#define FLATLANDS_BEHAVIOUR_H

class Game;
class Entity;

class Behaviour{
public:
    virtual bool tick(Entity* entity, Game* game, float fElapsedTime) = 0;
};

#endif //FLATLANDS_BEHAVIOUR_H
