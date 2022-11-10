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

    // set to true if this entity should have a
    // currChunk set, false otherwise
    virtual bool hasChunk() const {
        return true;
    }

    std::string getName() const {
        return name;
    }

    std::unique_ptr<Rectangle> getRectangle();

protected:
    std::string name;
    olc::vf2d location;
    olc::vf2d velocity;
    float health;

    bool touchingGround = false;
    bool canJump = false;

    olc::vf2d scaling;
    std::unique_ptr<olc::Sprite> sprTile;
    std::unique_ptr<olc::Decal> decalTile;

    Chunk* currChunk;

    const float gravity = 30.0f;

    float width, height, movingRight;
private:
    void detectTouchingGround(float touchThreshold);
};
