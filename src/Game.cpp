#include "olcPixelGameEngine.h"
#include "Game.h"
#include "Player.h"
#include "GlitterParticle.h"

#include <iostream>
#include <vector>

Game::Game(){
    sAppName = "TerrariaPP";
}

Game::~Game(){
    delete entityHandler;
    delete chunkHandler;
}

bool Game::OnUserCreate() {
    gamePos = {0.0f, 0.0f};

    entityHandler = new EntityHandler();
    chunkHandler = new ChunkHandler(200);

    // create a player and add the player to the game
    entityHandler->addEntity(new Player("Steve", {30.0f, 30.0f}));
    entityHandler->addEntity(new GlitterParticle({30.0f, 30.0f}, {0, 0}, 100));

    // Create a chunkg and add it to the game
    chunkHandler->addChunk(new Chunk({0, 0}));

    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    bool shouldContinue = processGlobalUserInput();

    // tick the game...
    shouldContinue = shouldContinue && tick(fElapsedTime);

    // ...and then render it
    render();

    return shouldContinue;
}

bool Game::tick(float fElapsedTime){
    updateEntityChunk();
    chunkHandler->tick(this, fElapsedTime);
    entityHandler->tick(this, fElapsedTime);

    return true;
}

void Game::render(){
    SetPixelMode(olc::Pixel::NORMAL);
    Clear(BACKGROUND_COLOUR);
    chunkHandler->render(this);
    entityHandler->render(this);

    DrawStringDecal({10, 10}, std::to_string(entityHandler->getNEntities()));
}

bool Game::processGlobalUserInput(){
    // do any processing of user input that isn't tied
    // an entity e.g. quitting the game, bringing up menus, etc.
    if (GetKey(olc::Key::ESCAPE).bHeld){
        return false;
    }

    return true;
}

void Game::updateEntityChunk(){
    // make sure that each entity has the correct chunk
    std::vector<Entity *> entities = entityHandler->getEntities();

    for(auto entity : entities){
        // check that the current chunk is correct
        olc::vf2d entityLoc = entity->getLocation();

        // start with checking the current chunk to see if we can avoid having
        // to iterate through the whole list of chunks
        if(entity->hasChunk() && entity->getChunk() != nullptr){
            Chunk* chunk = entity->getChunk();
            if(chunk->contains(entityLoc)){
                // beauty! can continue
                continue;
            }else{
                // current chunk is wrong
                entity->setChunk(nullptr);
            }
        }

        // looks like the current chunk either isn't set, or doesn't contain
        // the entity. Let's see if we can find a home for the entity.
        for(auto chunk : chunkHandler->getChunks()){
            if (chunk->contains(entityLoc)){
                entity->setChunk(chunk);
                break;
            }
        }
    }
}

void Game::addEntity(Entity *entity) {
    entityHandler->addEntity(entity);
}