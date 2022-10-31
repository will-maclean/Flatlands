#include "Player.h"
#include "Game.h"
#include "olcPixelGameEngine.h"

#include <iostream>

Player::Player(std::string name, olc::vf2d location)
: Entity(name, location,  {0.0f, 0.0f}, 100.0f, "./resources/sprites/crown.png", 16, 16){

    inputVel = {0, 0};
}


void Player::tick(Game* game, float fElapsedTime) {
    // update the velocity based on the keyboard input
    velocity -= inputVel;

    inputVel = {0, 0};

    // left right
    if (game->GetKey(olc::Key::LEFT).bHeld) inputVel.x -= MAX_SPEED;
	if (game->GetKey(olc::Key::RIGHT).bHeld) inputVel.x += MAX_SPEED;

    // up down
    if (game->GetKey(olc::Key::UP).bHeld && canJump) inputVel.y -= JUMP_VEL;

    velocity += inputVel;

    Entity::tick(game, fElapsedTime);
}
