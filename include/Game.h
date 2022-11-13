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
        return TOUCH_THRESHOLD;
    }

    void setGamePos(olc::vf2d gamePos){
        this->mGamePos = gamePos;
    }

    olc::vf2d getGamePos() const {
        return mGamePos;
    }

    olc::vf2d getRenderOffset(){
        return mGamePos - CENTRE_SPOT;
    }

    olc::vf2d getCentrePos(){
        return CENTRE_SPOT;
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
    const float TOUCH_THRESHOLD = 0.1f;
    const float WORLD_MIN = 0;
    const float WORLD_MAX = 1024;
    const olc::vf2d CENTRE_SPOT = {120, 120};
    olc::vf2d mGamePos;
    Entity* mMainPlayer;

	EntityHandler* mEntityHandler;
	ChunkHandler* mChunkHandler;
};
