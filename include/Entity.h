#pragma once

#include <string>
#include <memory>
#include "olcPixelGameEngine.h"

class Game;
class Chunk;
class Rectangle;

class Entity{
public:
    Entity(std::string name, olc::vf2d location, olc::vf2d velocity, float health, std::string spritePath, float width, float height);
    
    virtual bool tick(Game* game, float fElapsedTime);
    virtual void render(Game* game);

    void setChunk(Chunk* chunk){
        this->mCurrChunk = chunk;
    }

    Chunk* getChunk() const{  // do we want this to be const??
        return this-> mCurrChunk;
    }

    olc::vf2d getLocation() const {
        return mLocation;
    }

    float getWidth() const {
        return mWidth;
    }

    float getHeight() const {
        return mHeight;
    }

    // set to true if this entity should have a
    // mCurrChunk set, false otherwise
    virtual bool hasChunk() const {
        return true;
    }

    std::string getName() const {
        return mName;
    }

    std::unique_ptr<Rectangle> getRectangle();

    void setVelocity(olc::vf2d velocity){
        mVelocity = velocity;
    }

protected:
    std::string mName;
    olc::vf2d mLocation;
    olc::vf2d mVelocity;
    float mHealth;

    bool mTouchingGround = false;
    bool mCanJump = false;

    olc::vf2d mScaling;
    std::unique_ptr<olc::Sprite> mSprTile;
    std::unique_ptr<olc::Decal> mDecalTile;

    Chunk* mCurrChunk;

    const float mGravity = 40.0f;

    float mWidth, mHeight;

    bool mMovingRight;
private:
    void detectTouchingGround(float touchThreshold);
};
