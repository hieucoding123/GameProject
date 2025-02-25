#include <iostream>
#include "Game.h"
#include "TextureManager.h"

SDL_Texture* playerTex;

SDL_Renderer* Game::renderer = nullptr;

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
	playerTex = TextureManager::LoadTexture("C:/Users/Admin/source/repos/GameProject/assets/player.png");

	srcRect.x = srcRect.y = 0;

	srcRect.w = destRect.w = 32;
	srcRect.h = destRect.h = 64;

	destRect.x = destRect.y = 0;
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
	k++;
	srcRect.x = srcRect.y = 0;

	srcRect.w = destRect.w = 32;
	srcRect.h = destRect.h = 64;

	destRect.x = destRect.y = k;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	

	SDL_RenderCopy(renderer, playerTex, &srcRect, &destRect);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game cleaned" << std::endl;
}