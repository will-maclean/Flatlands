#include "olcPixelGameEngine.h"
#include "Game.h"
#include "Player.h"
#include "GlitterParticle.h"
#include "Rat.h"
#include <memory>
#include <iostream>
#include <vector>

Game::Game(){
    sAppName = "TerrariaPP";
    mMainPlayer = nullptr;
}

Game::~Game(){
    delete mEntityHandler;
    delete mChunkHandler;
}

bool Game::OnUserCreate() {
    mGamePos = {0.0f, 0.0f};

    mEntityHandler = new EntityHandler();
    mChunkHandler = new ChunkHandler(200);

    // create a player and add the player to the game
    mMainPlayer = new Player("Steve", {30.0f, 30.0f});
    addEntity(mMainPlayer);
    addEntity(new Rat({30, 30}));
    addEntity(new Rat({60, 30}));
    addEntity(new Rat({90, 30}));

    // Create a chunkg and add it to the game
    mChunkHandler->addChunk(new Chunk({0, 0}));

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
    mChunkHandler->tick(this, fElapsedTime);
    mEntityHandler->tick(this, fElapsedTime);

    return true;
}

void Game::render(){
    SetPixelMode(olc::Pixel::NORMAL);
    Clear(BACKGROUND_COLOUR);
    mChunkHandler->render(this);
    mEntityHandler->render(this);

    DrawStringDecal({10, 10}, std::to_string(mEntityHandler->getNEntities()));
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
    std::vector<Entity *> entities = mEntityHandler->getEntities();

    for(auto entity : entities){
        // check that the current chunk is correct
        olc::vf2d entityLoc = entity->getLocation();

        // start with checking the current chunk to see if we can avoid having
        // to iterate through the whole list of mChunks
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
        for(auto chunk : mChunkHandler->getChunks()){
            if (chunk->contains(entityLoc)){
                entity->setChunk(chunk);
                break;
            }
        }
    }
}

void Game::addEntity(Entity *entity) {
    mEntityHandler->addEntity(entity);
}

std::shared_ptr<Rectangle> Game::getScreenRect() const{
    olc::vf2d anchorPos = {mGamePos.x - ScreenWidth() / 2, mGamePos.y - ScreenHeight() / 2};
    return std::make_shared<Rectangle>(anchorPos, ScreenWidth(), ScreenHeight());
}