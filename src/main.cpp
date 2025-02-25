#include <iostream>
#include <SDL_image.h>
#include "Game.h"
#include "Const.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game;

	int xpos = SDL_WINDOWPOS_CENTERED;
	int ypos = SDL_WINDOWPOS_CENTERED;

	game->init("Game", xpos, ypos, WIDTH, HIGH, false);
	while (game->running())
	{
		Uint32 frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		int frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	
	std::cout << "GAME OVER!" << std::endl;

	return 0;
}