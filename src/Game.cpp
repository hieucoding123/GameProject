#include "Game.h"
#include "GameObjects/GameObject.h"
#include "Map.h"
#include "GameObjects/Sasuke.h"
#include "GameObjects/Akainu.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WIDTH, HIGH };
std::unique_ptr<AudioManager> Game::audioManager = std::make_unique<AudioManager>();

std::vector<std::unique_ptr<Tile>> Game::tiles;
EffectManager Game::effectManager;

int Game::MAP_SCALE = 2;

Sasuke* sasuke = nullptr;
Akainu* akainu = nullptr;

Map* map;

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

	audioManager->init();

	map->LoadMap(tileMapPath);

	sasuke = new Sasuke;
	sasuke->init();
	sasuke->setPosition(camera.x + 100, GROUND * MAP_SCALE);
	sasuke->setCamera();

	akainu = new Akainu;
	akainu->init();
	akainu->setPosition(camera.x + camera.w - 100, GROUND * MAP_SCALE);
	akainu->setCamera();
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
	for (auto& t : Game::tiles)
	{
		t->update();
	}
	sasuke->update();
	sasuke->ADWSController();

	akainu->update();
	akainu->LRUDController();
	effectManager.update();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& t : Game::tiles)
	{
		t->draw();
	}

	sasuke->draw();
	akainu->draw();
	effectManager.draw();

	// Vẽ thanh máu và năng lượng
	TextureManager::DrawHP(0, 0, (sasuke->getHP() * HP_W) / HP, HPBG_COLOR, HP_COLOR);
	TextureManager::DrawEnergy(0, HP_H,
		(sasuke->getEnergy() * (HP_W - 20)) / ENERGY, ENGBG_COLOR, ENG_COLOR);
	
	TextureManager::DrawHP(camera.w - HP_W, 0,
		((HP - akainu->getHP()) * HP_W) / HP, HP_COLOR, HPBG_COLOR);
	TextureManager::DrawEnergy(camera.w - HP_W + 20, HP_H,
		((ENERGY - akainu->getEnergy()) * (HP_W - 20)), ENG_COLOR, ENGBG_COLOR);

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	audioManager->clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}

bool Game::AABB(const SDL_Rect& rec1, const SDL_Rect& rec2)
{
	return (rec1.x + rec1.w >= rec2.x &&
		rec2.x + rec2.w >= rec1.x &&
		rec1.y + rec1.h >= rec2.y &&
		rec2.y + rec2.h >= rec1.y);
}

void Game::playSound(int ID)
{
	audioManager->playSound(ID);
}
