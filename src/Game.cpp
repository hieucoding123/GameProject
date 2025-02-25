#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"

Manager manager;


SDL_Renderer* Game::renderer = nullptr;

Map* map;
auto& player(manager.addEntity());

SDL_Rect srcRect, destRect;

Game::Game()
{ }

Game::~Game()
{ }

void Game::init(const char* title, int xpos, int ypos, int width, int high, bool fullScreen)
{
	int flags = 0;
	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Initialized!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, high, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);

			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	player.addComponent<TransformComponent>(50, 50);
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
		
	default:
		break;
	}
}

int k = 0;

void Game::update()
{
	manager.refresh();
	manager.update();

	player.getComponent<TransformComponent>().position + 1;

	std::cout << player.getComponent<TransformComponent>().position;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	manager.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}