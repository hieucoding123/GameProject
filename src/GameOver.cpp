#include "GameOver.h"
#include "TextureManager.h"
#include "Const.h"

GameOver::GameOver()
{
	
}

GameOver::~GameOver()
{
	SDL_DestroyTexture(bgTexture);
}

bool GameOver::continueGame()
{
	isContinue = true;
	bgTexture = TextureManager::LoadTexture("assets/gameOver.png");
	srcRect = { 0, GAME_OVER_H, GAME_OVER_W, GAME_OVER_H };

	while (true)
	{
		SDL_PollEvent(&Game::event);
		if (Game::event.type == SDL_KEYDOWN)
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_a:
			srcRect.y = GAME_OVER_H;
			isContinue = true;
			Game::playSound(2);
			break;
		case SDLK_d:
			srcRect.y = 0;
			isContinue = false;
			Game::playSound(2);
			break;
		case SDLK_j:
			if (!isContinue) Game::playSound(8);
			return isContinue;
			break;
		default:
			break;
		}

		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, bgTexture, &srcRect, NULL);
		SDL_RenderPresent(Game::renderer);
	}
	// chưa kết thúc
	return false;
}