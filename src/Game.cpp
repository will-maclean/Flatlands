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
}

bool Game::OnUserCreate() {
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {

    chunkHandler->tick(fElapsedTime);
    entityHandler->tick(fElapsedTime);

    chunkHandler->render(this);
    entityHandler->render(this);

    return true;
}