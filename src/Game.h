#pragma once

#include "olcPixelGameEngine.h"
#include "EntityHandler.h"

class Game : public olc::PixelGameEngine
{
private:
	olc::vf2d gamePos;

	EntityHandler* entityHandler;

public:
	Game();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;
};