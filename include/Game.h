#pragma once

#include "olcPixelGameEngine.h"
#include "EntityHandler.h"
#include "ChunkHandler.h"

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
private:
	const olc::Pixel BACKGROUND_COLOUR = {79, 46, 223};  // {r, g, b, a=1}
    const float touchThreshold = 0.1f;
    olc::vf2d gamePos;

	EntityHandler* entityHandler;
	ChunkHandler* chunkHandler;
};
