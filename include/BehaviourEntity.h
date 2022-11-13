//
// Created by Will Maclean on 13/11/2022.
//

#ifndef FLATLANDS_BEHAVIOURENTITY_H
#define FLATLANDS_BEHAVIOURENTITY_H

#include "Entity.h"
#include "olcPixelGameEngine.h"
#include <map>
#include <string>

class Behaviour;

class BehaviourEntity : public Entity{
public:
    BehaviourEntity(std::string name, olc::vf2d location, olc::vf2d velocity, float health, std::string spritePath, float width, float height);
    ~BehaviourEntity();

    bool tick(Game* game, float fElapsedTime) override;

    void setCurrBehaviour(Behaviour* behaviour);

private:
    Behaviour* mCurrBehaviour;
    std::map<int, Behaviour*> mBehaviours;
};

#endif //FLATLANDS_BEHAVIOURENTITY_H
