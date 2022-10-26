#pragma once

#include "olcPixelGameEngine.h"
#include "EntityHandler.h"
#include "ChunkHandler.h"

class Game : public olc::PixelGameEngine
{
private:
	olc::vf2d gamePos;

	EntityHandler* entityHandler;
	ChunkHandler* chunkHandler;

public:
	Game();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;
};