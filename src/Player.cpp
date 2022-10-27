#include "Player.h"
#include "Game.h"
#include "olcPixelGameEngine.h"

#include <iostream>

Player::Player(std::string name, olc::vf2d location)
: Entity(name, location,  {0.0f, 0.0f}, 100.0f, "./resources/sprites/crown.png"){

}


void Player::tick(Game* game, float fElapsedTime){
    // update the velocity based on the keyboard input

    // left right
    if (game->GetKey(olc::Key::LEFT).bHeld) velocity.x -= MAX_SPEED;
	if (game->GetKey(olc::Key::RIGHT).bHeld) velocity.x += MAX_SPEED;

    // up down
    if (game->GetKey(olc::Key::LEFT).bHeld) velocity.x -= MAX_SPEED;
	if (game->GetKey(olc::Key::RIGHT).bHeld) velocity.x += MAX_SPEED;

    Entity::tick(game, fElapsedTime);
}
