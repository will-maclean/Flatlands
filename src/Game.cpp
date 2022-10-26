#include "olcPixelGameEngine.h"
#include "Game.h"
#include "Player.h"

Game::Game(){
    sAppName = "TerrariaPP";

    gamePos = {0.0f, 0.0f};

    // create a player and add the player to the game
    // entityHandler->addEntity(new Player("Steve", {static_cast<float>(ScreenWidth())/2, static_cast<float>(ScreenHeight())/2}));
    entityHandler->addEntity(new Player());
}

bool Game::OnUserCreate() {
    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    // called once per frame
    for (int x = 0; x < ScreenWidth(); x++)
        for (int y = 0; y < ScreenHeight(); y++)
            Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand()% 256));

    entityHandler->tick(fElapsedTime);

    entityHandler->render(this);

    return true;
}