#include <iostream>
#include "Game.h"
#include "Const.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;

Map* map;

enum groupLabels : Group
{
	p1Group,
	p2Group,
	mapGroup

};

auto& tiles(manager.getGroup(mapGroup));
auto& player1Group(manager.getGroup(p1Group));
auto& player2Group(manager.getGroup(p2Group));

auto& player1(manager.addEntity());
auto& player2(manager.addEntity());

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
	map->LoadMap("assets/TileMap.txt");

	player1.addComponent<TransformComponent>(100, 100);
	player1.addComponent<SpriteComponent>("assets/player.png");
	player1.addGroup(p1Group);
}

void Game::handleEvents()
{
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

void Game::update()
{
	manager.refresh();
	manager.update();

	player1.getComponent<TransformComponent>().position + 1;

	std::cout << player1.getComponent<TransformComponent>().position;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& e : tiles)
	{
		e->draw();
	}
	for (auto& e : player1Group)
	{
		e->draw();
	}
	for (auto& e : player2Group)
	{
		e->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}

void Game::addTile(int tileX, int tileY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	
	tile.addComponent<TileComponent>(tileX, tileY, xpos, ypos);
	tile.addGroup(mapGroup);
}