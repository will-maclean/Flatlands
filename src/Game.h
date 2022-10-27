#pragma once

#include "olcPixelGameEngine.h"
#include "EntityHandler.h"
#include "ChunkHandler.h"

class Game : public olc::PixelGameEngine
{
private:
	const olc::Pixel BACKGROUND_COLOUR = {79, 46, 223};  // {r, g, b, a=1}
	olc::vf2d gamePos;

	EntityHandler* entityHandler;
	ChunkHandler* chunkHandler;

public:
	Game();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

	bool tick(float fElapsedTime);

	void render();
};