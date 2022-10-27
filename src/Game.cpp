#include "olcPixelGameEngine.h"
#include "Game.h"
#include "Player.h"

#include <iostream>

Game::Game(){
    sAppName = "TerrariaPP";

    gamePos = {0.0f, 0.0f};
    
    entityHandler = new EntityHandler();
    chunkHandler = new ChunkHandler();

    // create a player and add the player to the game
    entityHandler->addEntity(new Player("Steve", {30.0f, 30.0f}));

    // Create a chunkg and add it to the game
    chunkHandler->addChunk(new Chunk({0, 0}));
}

bool Game::OnUserCreate() {
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {

    // tick the game...
    bool shouldContinue = tick(fElapsedTime);

    // ...and then render it
    render();

    return shouldContinue;
}

bool Game::tick(float fElapsedTime){
    chunkHandler->tick(fElapsedTime);
    entityHandler->tick(this, fElapsedTime);

    return true;
}

void Game::render(){
    SetPixelMode(olc::Pixel::NORMAL);
    Clear(BACKGROUND_COLOUR);
    chunkHandler->render(this);
    entityHandler->render(this);
}