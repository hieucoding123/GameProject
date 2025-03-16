#include "Tile.h"
#include "TextureManager.h"
#include "PlaySection.h"

Tile::Tile(int tileX, int tileY, int xpos, int ypos)
{
	texture = TextureManager::LoadTexture(imageTilePath);

	srcRect.x = tileX;
	srcRect.y = tileY;
	srcRect.h = BLOCK_H;
	srcRect.w = BLOCK_W;
	
	destRect.x = x = xpos * PlaySection::MAP_SCALE;
	destRect.y = y = ypos * PlaySection::MAP_SCALE;
	destRect.w = BLOCK_W * PlaySection::MAP_SCALE;
	destRect.h = BLOCK_H * PlaySection::MAP_SCALE;
}

void Tile::update()
{
	destRect.x = x - PlaySection::camera.x;
	destRect.y = y - PlaySection::camera.y;
}

void Tile::draw()
{
	TextureManager::Draw(texture, &srcRect, &destRect, SDL_FLIP_NONE);
}