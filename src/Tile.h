#pragma once

#include <string>
#include "olcPixelGameEngine.h"

class Game;

class Tile{
private:
    std::unique_ptr<olc::Sprite> sprTile;

public:
    Tile(std::string spritePath);
    Tile();

    void tick(float fElapsedTime);

    void render(Game* game, olc::vi2d location);
};

class EmptyTile : public Tile{
public:
    EmptyTile();
};

class DirtTile : public Tile{
public:
    DirtTile();
};