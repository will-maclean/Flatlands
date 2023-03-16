//
// Created by Will Maclean on 13/11/2022.
//

#pragma once

class Game;
class Entity;

class Behaviour{
public:
  Behaviour() = default;
  ~Behaviour() = default;

    virtual bool tick(Entity* entity, Game* game, float fElapsedTime) = 0;
};
