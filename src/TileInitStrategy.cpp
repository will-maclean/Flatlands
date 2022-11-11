#include "TileInitStrategy.h"
#include "Chunk.h"
#include "Tile.h"
#include "olcPixelGameEngine.h"
#include <cstdlib>
#include <random>

void fillAll(Chunk* chunk){
    olc::vf2d chunkAnchorLocation = chunk->getAnchorLocation();

    for(int i = 0; i < chunk->getHeight(); i++){
        for(int j = 0; j < chunk->getWidth(); j++){
            olc::vf2d anchorLocation = {chunkAnchorLocation.x + j * chunk->getTileWidth(), chunkAnchorLocation.y + i * chunk->getTileHeight()};
            chunk->setTile(new DirtTile(anchorLocation), j, i);
        }
    }
}

void flatWithHoles(Chunk* chunk){
    // top 10% of chunk -> EmptyTile
    // lower 75% of chunk -> 90% DirtBlock, 10% EmptyTile

    int threshold = chunk->getHeight() * 0.1;

    bool emptyMap[chunk->getHeight()][chunk->getWidth()];

    olc::vf2d chunkAnchorLocation = chunk->getAnchorLocation();

    for(int i = 0; i < chunk->getHeight(); i++){
        for(int j = 0; j < chunk->getWidth(); j++){
            olc::vf2d anchorLocation = {chunkAnchorLocation.x + j * chunk->getTileWidth(), chunkAnchorLocation.y + i * chunk->getTileHeight()};
            if(i < threshold){
                // EmptyTile only
                chunk->setTile(new EmptyTile(anchorLocation), j, i);
                emptyMap[i][j] = true;
            }else{
                // 90% dirt, 10% chance empty
                int r = std::rand() % 100;
                if(r < 70){
                    if(i >=2 && emptyMap[i-1][j] && emptyMap[i-2][j]){
                        chunk->setTile(new GrassyDirtTile(anchorLocation), j, i);
                    }else{
                        chunk->setTile(new DirtTile(anchorLocation), j, i);
                    }
                    emptyMap[i][j] = false;
                }else{
                    chunk->setTile(new EmptyTile(anchorLocation), j, i);
                    emptyMap[i][j] = true;
                }
            }
        }
    }
}

void noisyTerrain(Chunk* chunk){
    // make an array of noise
    int noise[chunk->getWidth()];

    noise[0] = 0.1 * chunk->getHeight();

    std::default_random_engine generator;
    std::normal_distribution<float> distribution(0.0,1.0);

    for(int i = 1; i < chunk->getWidth(); i++){
        noise[i] = noise[i-1] + (int)distribution(generator);
    }

    olc::vf2d chunkAnchorLocation = chunk->getAnchorLocation();
    for(int i = 0; i < chunk->getWidth(); i++) {
        for (int j = 0; j < chunk->getHeight(); j++) {
            olc::vf2d anchorLocation = {chunkAnchorLocation.x + i * chunk->getTileWidth(), chunkAnchorLocation.y + j * chunk->getTileHeight()};
            if(j < noise[i]){
                // empty tile
                chunk->setTile(new EmptyTile(anchorLocation), i, j);
            }else if (j == noise[i]){
                // grassy tile
                chunk->setTile(new GrassyDirtTile(anchorLocation), i, j);
            }else{
                // dirt tile
                chunk->setTile(new DirtTile(anchorLocation), i, j);
            }
        }
    }

}

void defaultTileInitStrategy(Chunk* chunk){
//    flatWithHoles(chunk);
    noisyTerrain(chunk);
}
