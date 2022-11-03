#include "Player.h"
#include "Game.h"
#include "olcPixelGameEngine.h"
#include "GlitterParticle.h"
#include <stdlib.h>

Player::Player(std::string name, olc::vf2d location)
: Entity(name, location,  {0.0f, 0.0f}, 100.0f, "./resources/sprites/pixel_cat.png", 16, 16){

    inputVel = {0, 0};
}


bool Player::tick(Game* game, float fElapsedTime) {
    // update the velocity based on the keyboard input
    velocity -= inputVel;

    inputVel = {0, 0};

    // left right
    if (game->GetKey(olc::Key::LEFT).bHeld) inputVel.x -= MAX_SPEED;
	if (game->GetKey(olc::Key::RIGHT).bHeld) inputVel.x += MAX_SPEED;

    // up down
    if (game->GetKey(olc::Key::UP).bHeld && canJump){
        velocity.y -= JUMP_VEL;
    }
    if(inputVel.mag() > 0){
        inputVel = MAX_SPEED * inputVel.norm();
    }

    velocity += inputVel;

    Entity::tick(game, fElapsedTime);

    game->setGamePos(location);

    if (game->GetKey(olc::Key::R).bPressed){
        fartGlitter(game);
    }

    return true;
}

void Player::render(Game* game){
    game->SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
    game->DrawDecal(game->getCentrePos(), decalTile.get());
}

void Player::fartGlitter(Game* game) {
    // I am a sellout

    for(int i = 0; i < 5; i++){
        olc::vf2d spawLoc = location;
        olc::vf2d spawnVel {static_cast<float>(std::rand() % 10 - 5), -10};

        game->addEntity(new GlitterParticle(spawLoc, spawnVel, 10));
    }
}
