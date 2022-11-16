#pragma once

#include <vector>

#include "Entity.h"

class Game;

class EntityHandler{
public:
    EntityHandler();

    void addEntity(Entity* entity);

    // void removeEntity(Entity* entity);

    void tick(Game* game, float fElapsedTime);

    void render(Game* game);

    std::vector<Entity *> getEntities(){
        return mEntities;
    }

    int getNEntities() const {
        return mEntities.size();
    }

private:
    std::vector<Entity *> mEntities;
};