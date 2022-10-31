#pragma once

#include <string>
#include "olcPixelGameEngine.h"

class Game;
class Entity;

class Tile{
private:
    std::unique_ptr<olc::Sprite> sprTile;
    bool mIsSolid;
    olc::Sprite::Flip flip;
    olc::vf2d anchorLocation;

    int tileWidth = 16;  //TODO: fix this
    int tileHeight = 16;

public:
    Tile(olc::vf2d anchorLocation, std::string spritePath, bool randomFlip, bool mIsSolid);
    Tile(olc::vf2d anchorLocation, bool mIsSolid);

    void tick(float fElapsedTime);

    void render(Game* game, olc::vi2d location);

    bool isSolid() const{
        return this->mIsSolid;
    }
    
    int getTileWidth() const {
        return tileWidth;
    }

    int getTileHeight() const {
        return tileHeight;
    }

    olc::vf2d getAnchorLocation() const {
        return anchorLocation;
    }

    bool entityCollision(Entity* entity, olc::vf2d testLocation);

    bool entityStandingOn(Entity* entity, float touchThreshold);
};

class EmptyTile : public Tile{
public:
    EmptyTile(olc::vf2d anchorLocation);
};

class DirtTile : public Tile{
public:
    DirtTile(olc::vf2d anchorLocation);
};

class GrassyDirtTile : public Tile{
public:
    GrassyDirtTile(olc::vf2d anchorLocation);
};
