#include "Interface.h"
#include "Game.h"
#include "TextureManager.h"
#include "Const.h"

Interface::Interface()
{
	
}

Interface::~Interface()
{
	SDL_DestroyTexture(interfaceTex);
	SDL_DestroyTexture(buttonsTex);
}

void Interface::init()
{
	mode = 0;
	players = 2;

	interfaceTex = TextureManager::LoadTexture(INTERFACE_PATH);
	buttonsTex = TextureManager::LoadTexture(BUTTONS_PATH);

	srcBut1.w = srcBut2.w = BUTTON_W;
	srcBut1.h = srcBut2.h = BUTTON_H;

	destBut1.x = destBut2.x = WIDTH / 2 - BUTTON_W;
	destBut1.y = 600;

	destBut2.y = 800;
}
int Interface::selectMode()
{
	srcBut1.x = 0;
	srcBut2.x = BUTTON_W;
	srcBut1.y = srcBut2.y = 0;

	destBut1.w = BUTTON_W * 2 + 10;
	destBut1.h = BUTTON_H * 2 + 10;
	destBut2.w = BUTTON_W * 2;
	destBut2.h = BUTTON_H * 2;
	while (true)
	{
		while (SDL_PollEvent(&Game::event))
		{
			if (Game::event.type == SDL_QUIT)
			{
				chooseSuccess = false;
				return mode;
			}
			if (Game::event.type == SDL_KEYDOWN)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					mode = 0;
					destBut1.w = BUTTON_W * 2 + 10;
					destBut1.h = BUTTON_H * 2 + 10;
					destBut2.w = BUTTON_W * 2;
					destBut2.h = BUTTON_H * 2;
					Game::playSound(2);
					break;
				case SDLK_s:
					mode = 1;
					destBut1.w = BUTTON_W * 2;
					destBut1.h = BUTTON_H * 2;
					destBut2.w = BUTTON_W * 2 + 10;
					destBut2.h = BUTTON_H * 2 + 10;
					Game::playSound(2);
					break;
				case SDLK_j:				// confirm
					Game::playSound(3);
					return mode;
				default:
					break;
				}
			}
			draw();
		}
	}
}

int Interface::selectNumOfPlayers()
{
	// nếu chọn không thành
	if (!chooseSuccess) return players;

	// chuyển sang nút hiển thị số người chơi
	srcBut1.x = BUTTON_W * 2;
	srcBut2.x = BUTTON_W * 3;
	srcBut1.y = srcBut2.y = 0;

	destBut1.w = BUTTON_W * 2 + 10;
	destBut1.h = BUTTON_H * 2 + 10;
	destBut2.w = BUTTON_W * 2;
	destBut2.h = BUTTON_H * 2;

	while (true)
	{
		while (SDL_PollEvent(&Game::event))
		{
			if (Game::event.type == SDL_QUIT)
			{
				chooseSuccess = false;
				return players;
			}
			if (Game::event.type == SDL_KEYDOWN)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					players = 2;
					destBut1.w = BUTTON_W * 2 + 10;
					destBut1.h = BUTTON_H * 2 + 10;
					destBut2.w = BUTTON_W * 2;
					destBut2.h = BUTTON_H * 2;
					Game::playSound(2);
					break;
				case SDLK_s:
					players = 1;
					destBut1.w = BUTTON_W * 2;
					destBut1.h = BUTTON_H * 2;
					destBut2.w = BUTTON_W * 2 + 10;
					destBut2.h = BUTTON_H * 2 + 10;
					Game::playSound(2);
					break;
				case SDLK_j:				// confirm
					Game::playSound(3);
					return players;
				default:
					break;
				}
			}
		}
		draw();
	}
}

void Interface::draw()
{
	SDL_RenderClear(Game::renderer);
	SDL_RenderCopy(Game::renderer, interfaceTex, NULL, NULL);
	SDL_RenderCopy(Game::renderer, buttonsTex, &srcBut1, &destBut1);
	SDL_RenderCopy(Game::renderer, buttonsTex, &srcBut2, &destBut2);
	SDL_RenderPresent(Game::renderer);
}