#include "Tile.h"
#include "Game.h"

Tile::Tile(std::string spritePath){
    sprTile = std::make_unique<olc::Sprite>(spritePath);
}

Tile::Tile(){
    sprTile = nullptr;
}

void Tile::tick(float fElapsedTime){
    //do nothing for now
}

void Tile::render(Game* game, olc::vi2d location){
    // just render the sprite, if defined
    if(sprTile != nullptr){
        game->DrawSprite(location, sprTile.get());
    }
}

EmptyTile::EmptyTile()
    : Tile(){
}

DirtTile::DirtTile()
    : Tile("./resources/sprites/tut_tile.png"){

    }