#include <iostream>
#include "Game.h"
#include "Const.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WIDTH, HIGH };
int Game::MAP_SCALE = 2;

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

	// đặt camera ở giữa
	camera.x = (WIDTH * MAP_SCALE - WIDTH) / 2;
	camera.y = (HIGH * MAP_SCALE - HIGH);

	map->LoadMap(tileMapPath);

	player1.addComponent<TransformComponent>(camera.x + 100, GROUND*MAP_SCALE, 48, 75, 2);
	player1.addComponent<SpriteComponent>("assets/sasuke.png", true);
	player1.addComponent<AnimationComponent>();
	player1.addComponent<KeyboardController>();
	player1.addComponent<ColliderComponent>();
	player1.addGroup(p1Group);

	player2.addComponent<TransformComponent>(camera.x + WIDTH - 100, GROUND*MAP_SCALE, 46, 80, 2);
	player2.addComponent<SpriteComponent>("assets/akainu_stand.png", true);
	player2.addComponent<AnimationComponent>();
	player2.addComponent<KeyboardController>();
	player2.addComponent<ColliderComponent>();
	player2.addGroup(p2Group);
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

	int distance = std::abs(player1.getComponent<TransformComponent>().position.x - player2.getComponent<TransformComponent>().position.x);

	if (distance >= camera.w) {
		;
	}

	// camera chạy theo
	//camera.x = player1.getComponent<TransformComponent>().position.x - (WIDTH * 1.0 / 2);
	//camera.y = player1.getComponent<TransformComponent>().position.y - (HIGH * 1.0 / 2);



	if (camera.x < 0) camera.x = 0;
	if (camera.x > WIDTH) camera.x = WIDTH;
	if (camera.y < 0) camera.y = 0;
	if (camera.y > HIGH) camera.y = HIGH;

	if (Game::AABB(player1.getComponent<ColliderComponent>().attackBox,
		player2.getComponent<ColliderComponent>().rect))
	{
		if (player1.attrib.isHitting) {
			std::cout << "Var ";
			player2.attrib.hp -= player1.attrib.damage;
			player1.attrib.energy++;
			std::cout << "Player 2 :" << "HP = " << player2.attrib.hp << std::endl;
		}
		if (player2.attrib.isHitting) {
			player1.attrib.hp -= player2.attrib.damage;
			player2.attrib.energy++;
			std::cout << "Player 1 :" << "HP = " << player1.attrib.hp << std::endl;
		}

	}

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

	int barWidth = 200;  // Chiều rộng thanh máu
	int barHeight = 20;

	int fillWidth = (player1.attrib.hp * barWidth) / HP;
	SDL_Rect fillRect = { 0, 0, fillWidth, barHeight };
	SDL_SetRenderDrawColor(renderer, 234, 164, 31, 255);
	SDL_RenderFillRect(renderer, &fillRect);
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

bool Game::AABB(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
	return SDL_HasIntersection(&rect1, &rect2);
}