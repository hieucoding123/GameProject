#include "Game.h"
#include "GameObjects/GameObject.h"
#include "Map.h"
#include "GameObjects/Sasuke.h"
#include "GameObjects/Akainu.h"
#include "SelectionSection.h"
#include "PlaySection.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

PlaySection* playSection = new PlaySection;
std::unique_ptr<AudioManager> Game::audioManager = std::make_unique<AudioManager>();

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
	audioManager->init();

	// Phần chọn nhân vật
	SelectionSection::selectionLoad();
	std::vector<int> ID = SelectionSection::Selection();
	
	// Khởi tạo nhân vật và game
	playSection->playLoad();
	playSection->init(ID);
}

void Game::handleEvents()
{
	// Xử lý sự kiện chung
	SDL_PollEvent(&event);

	playSection->handleEvents();
	if (!playSection->playing())
	{
		isRunning = false;
	}

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
	// Phần cập nhật game
	playSection->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	// Phần vẽ game
	playSection->render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	playSection->clean();
	delete playSection;
	playSection = nullptr;
	audioManager->clean();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}

void Game::playSound(int ID)
{
	audioManager->playSound(ID);
}