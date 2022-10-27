#include "Tile.h"
#include "Game.h"
#include <stdlib.h>

Tile::Tile(std::string spritePath, bool randomFlip){
    sprTile = std::make_unique<olc::Sprite>(spritePath);

    if(randomFlip){
        int flipType = rand() % 3;

        flip = olc::Sprite::Flip(flipType);
    }else{
        flip = olc::Sprite::Flip(0);
    }
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
        game->DrawSprite(location, sprTile.get(), 1, flip);
        // game->DrawSprite()
    }
}

EmptyTile::EmptyTile()
    : Tile(){
}

DirtTile::DirtTile()
    : Tile("./resources/sprites/pixel_dirt.png", true){

    }

GrassyDirtTile::GrassyDirtTile()
    : Tile("./resources/sprites/pixel_grassy_dirt.png", false){

    }