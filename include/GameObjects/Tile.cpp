#include "Tile.h"
#include "TextureManager.h"
#include "Game.h"

Tile::Tile(int tileX, int tileY, int xpos, int ypos)
{
	texture = TextureManager::LoadTexture(imageTilePath);

	srcRect.x = tileX;
	srcRect.y = tileY;
	srcRect.h = BLOCK_H;
	srcRect.w = BLOCK_W;
	
	destRect.x = x = xpos * Game::MAP_SCALE;
	destRect.y = y = ypos * Game::MAP_SCALE;
	destRect.w = BLOCK_W * Game::MAP_SCALE;
	destRect.h = BLOCK_H * Game::MAP_SCALE;
}

void Tile::update()
{
	destRect.x = x - Game::camera.x;
	destRect.y = y - Game::camera.y;
}

void Tile::draw()
{
	TextureManager::Draw(texture, &srcRect, &destRect, SDL_FLIP_NONE);
}