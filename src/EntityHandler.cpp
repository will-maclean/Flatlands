#include "EntityHandler.h"
#include <vector>

EntityHandler::EntityHandler(){

}

void EntityHandler::addEntity(Entity* entity){
    mEntities.push_back(entity);
}

void EntityHandler::tick(Game* game, float fElapsedTime){
    std::vector<int> deleteIdxs;

    for(int i = 0; i < mEntities.size(); i++){
        Entity* entity = mEntities.at(i);

        if(!entity->tick(game, fElapsedTime)) {
            deleteIdxs.push_back(i);
        }
    }

    std::sort(deleteIdxs.begin(), deleteIdxs.end(), std::greater<int>());

    for(auto idx : deleteIdxs){
        Entity* entity = mEntities.at(idx);

        mEntities.erase(mEntities.begin() + idx);

        delete entity;
    }
}

void EntityHandler::render(Game* game){
    for(auto entity : mEntities){
        entity->render(game);
    }
}