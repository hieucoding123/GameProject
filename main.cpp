#include <iostream>
#include <SDL.h>
#include "Game.h"

const int WIDTH = 800;
const int HIGH = 600;

Game* game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game;

	int xpos = SDL_WINDOWPOS_CENTERED;
	int ypos = SDL_WINDOWPOS_CENTERED;

	game->init("Game", xpos, ypos, WIDTH, HIGH, false);
	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();
	
	std::cout << "GAME OVER!" << std::endl;

	return 0;
}