#include "Player.h"
#include "Game.h"
#include "olcPixelGameEngine.h"
#include "GlitterParticle.h"
#include <stdlib.h>

Player::Player(std::string name, olc::vf2d location)
: Entity(name, location,  {0.0f, 0.0f}, 100.0f, "./resources/sprites/pixel_cat.png", 12, 12){

    mInputVel = {0, 0};
}


bool Player::tick(Game* game, float fElapsedTime) {
    // update the mVelocity based on the keyboard input
    mVelocity -= mInputVel;

    mInputVel = {0, 0};

    // left right
    if (game->GetKey(olc::Key::LEFT).bHeld) mInputVel.x -= MAX_SPEED;
	if (game->GetKey(olc::Key::RIGHT).bHeld) mInputVel.x += MAX_SPEED;

    // up down
    if (game->GetKey(olc::Key::UP).bHeld && mCanJump){
        mVelocity.y -= JUMP_VEL;
    }
    if(mInputVel.mag() > 0){
        mInputVel = MAX_SPEED * mInputVel.norm();
    }

    mVelocity += mInputVel;

    Entity::tick(game, fElapsedTime);

    game->setGamePos(mLocation);

    if (game->GetKey(olc::Key::R).bPressed){
        fartGlitter(game);
    }

    return true;
}

void Player::render(Game* game){
    game->SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency

    olc::vf2d drawPos = game->getCentrePos();

    olc::vf2d drawScaling = mScaling;

    if(mMovingRight){
        // facing right!
        drawScaling.x *= -1;
        drawPos.x += mWidth;
    }

    game->DrawDecal(drawPos, mDecalTile.get(), drawScaling);
}

void Player::fartGlitter(Game* game) {
    // I am a sellout

    for(int i = 0; i < 5; i++){
        olc::vf2d spawLoc = mLocation;
        olc::vf2d spawnVel {static_cast<float>(std::rand() % 10 - 5), -100};

        game->addEntity(new GlitterParticle(spawLoc, spawnVel, 5));
    }
}
