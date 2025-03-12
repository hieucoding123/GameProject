#pragma once

#include "Const.h"

class Tile
{
public:
	Tile(int tileX, int tileY, int xpos, int ypos);
	void update();
	void draw();
private:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	int x, y;	
};