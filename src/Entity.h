#pragma once

#include <string>
#include "olcPixelGameEngine.h"

class Game;
class Chunk;

class Entity{
private:
    const float gravity = 5.0f;
    float width, height;

protected:
    std::string name;
    olc::vf2d location;
    olc::vf2d velocity;
    float health;


    std::unique_ptr<olc::Sprite> sprTile;

    Chunk* currChunk;

public:
    Entity(std::string name, olc::vf2d location, olc::vf2d velocity, float health, std::string spritePath, float width, float height);
    
    virtual void tick(Game* game, float fElapsedTime);
    void render(Game* game);

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
};
