#pragma once

#include "olcPixelGameEngine.h"
#include "EntityHandler.h"
#include "ChunkHandler.h"

class Entity;

class Game : public olc::PixelGameEngine{
public:
	Game();

	~Game();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

	bool processGlobalUserInput();

	bool tick(float fElapsedTime);

	void render();

	void updateEntityChunk();

    float getTouchThreshold() const{
        return touchThreshold;
    }

    void setGamePos(olc::vf2d gamePos){
        this->gamePos = gamePos;
    }

    olc::vf2d getGamePos() const {
        return gamePos;
    }

    olc::vf2d getRenderOffset(){
        return gamePos - centreSpot;
    }

    olc::vf2d getCentrePos(){
        return centreSpot;
    }

    float getWorldMin() const {
        return WORLD_MIN;
    }

    float getWorldMax() const {
        return WORLD_MAX;
    }

    void addEntity(Entity* entity);

    std::shared_ptr<Rectangle> getScreenRect() const;

private:
	const olc::Pixel BACKGROUND_COLOUR = {79, 46, 223};  // {r, g, b, a=1}
    const float touchThreshold = 0.1f;
    const float WORLD_MIN = 0;
    const float WORLD_MAX = 1024;
    const olc::vf2d centreSpot = {120, 120};
    olc::vf2d gamePos;
    Entity* mainPlayer;

	EntityHandler* entityHandler;
	ChunkHandler* chunkHandler;
};
