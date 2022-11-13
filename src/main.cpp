#include "Game.h"

int main()
{
	Game game;
	if (game.Construct(256, 240, 2, 2))
		game.Start();

	return 0;
}