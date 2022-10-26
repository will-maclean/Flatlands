#include "Player.h"
#include "Game.h"

#include <iostream>

Player::Player(std::string name, olc::vf2d location)
: Entity(name, location,  {0.0f, 0.0f}, 100.0f, "./resources/sprites/tut_tile.png"){

}


void Player::tick(float fElapsedTime){
    // do nothing for now
}

void Player::render(Game* game){
    game->DrawSprite(location, sprTile.get());
}