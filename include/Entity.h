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
    
    virtual void tick(Game* game, float fElapsedTime);
    virtual void render(Game* game);

    void setChunk(Chunk* chunk){
        this->currChunk = chunk;
    }

    Chunk* getChunk() const{  // do we want this to be const??
        return this-> currChunk;
    }

    olc::vf2d getLocation() const {
        return location;
    }

    float getWidth() const {
        return width;
    }

    float getHeight() const {
        return height;
    }

    std::unique_ptr<Rectangle> getRectangle();

protected:
    std::string name;
    olc::vf2d location;
    olc::vf2d velocity;
    float health;

    bool touchingGround = false;
    bool canJump = false;

    std::unique_ptr<olc::Decal> decalTile;

    Chunk* currChunk;

private:
    const float gravity = 0.1f;
    float width, height;

    void detectTouchingGround(float touchThreshold);
};
