﻿#include "Game.h"
#include "GameObjects/GameObject.h"
#include "Map.h"
#include "GameObjects/Sasuke.h"
#include "GameObjects/Akainu.h"
#include "Interface.h"
#include "SelectionSection.h"
#include "PlaySection.h"
#include "GameOver.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Interface* itf = new Interface;
PlaySection* playSection = new PlaySection;
GameOver* gameOver = new GameOver;

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
}

void Game::play()
{
	// Khi game chạy
	while (isRunning)
	{
		// Phần chọn chế độ và số người chơi
		int mode, players = 2;
		itf->init();
		mode = itf->selectMode();
		if (!itf->success())
		{
			isRunning = false;
			return;
		}
		if (mode != 0)						// chế độ survival
		{
			players = itf->selectNumOfPlayers();
			if (!itf->success())
			{
				isRunning = false;
				return;
			}
		}

		// Phần chọn nhân vật
		SelectionSection::selectionLoad();
		std::vector<int> ID = SelectionSection::Selection(players);
		

		// Khởi tạo nhân vật và game
		PlaySection::gameObjects.clear();

		playSection->playLoad();
		playSection->init(ID, mode);

		playSection->setPlaying(true);

		// Vòng lặp game
		while (playSection->playing())
		{
			Uint32 frameStart = SDL_GetTicks();

			playSection->handleEvents();
			playSection->update();
			playSection->render();

			int frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}
		}
		playSection->clean();
		
		// Kết thúc game
		playSound(12);		// âm thanh kết thúc
		if (!gameOver->continueGame())
		{
			isRunning = false;
		}
	}
}


void Game::clean()
{
	delete itf;
	itf = nullptr;
	delete playSection;
	playSection = nullptr;
	delete gameOver;
	gameOver = nullptr;
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