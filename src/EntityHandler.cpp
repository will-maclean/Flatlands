#include "EntityHandler.h"

EntityHandler::EntityHandler(){

}

void EntityHandler::addEntity(Entity* entity){
    entities.push_back(entity);
}

// void EntityHandler::removeEntity(Entity* entity){
//     entities.remove(entities.begin(), entities.end(), entity);
// }

void EntityHandler::tick(float fElapsedTime){
    for(auto entity : entities){
        entity->tick(fElapsedTime);
    }
}

void EntityHandler::render(Game* game){
    for(auto entity : entities){
        entity->render(game);
    }
}