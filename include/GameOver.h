#pragma once

#include "SDL.h"

class GameOver
{
public:
	GameOver();
	~GameOver();

	/*
	* Tùy chọn tiếp tục hoặc kết thúc game
	* @return true nếu kết thúc game
	*/
	bool continueGame();
private:
	SDL_Texture* bgTexture;
	SDL_Rect srcRect;
	bool isContinue;
};