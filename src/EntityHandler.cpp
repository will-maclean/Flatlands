#include "EntityHandler.h"
#include <vector>

EntityHandler::EntityHandler(){

}

void EntityHandler::addEntity(Entity* entity){
    entities.push_back(entity);
}

void EntityHandler::tick(Game* game, float fElapsedTime){
    std::vector<int> deleteIdxs;

    for(int i = 0; i < entities.size(); i++){
        Entity* entity = entities.at(i);

        if(!entity->tick(game, fElapsedTime)) {
            deleteIdxs.push_back(i);
        }
    }

    std::sort(deleteIdxs.begin(), deleteIdxs.end(), std::greater<int>());

    for(auto idx : deleteIdxs){
        Entity* entity = entities.at(idx);

        entities.erase(entities.begin() + idx);

        delete entity;
    }
}

void EntityHandler::render(Game* game){
    for(auto entity : entities){
        entity->render(game);
    }
}