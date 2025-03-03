#pragma once

#include "Components.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	// vị trí trên màn hình
	int x;
	int y;

	TileComponent() = default;
	TileComponent(int tileX, int tileY, int xpos, int ypos)
	{
		texture = TextureManager::LoadTexture(imageTilePath);

		srcRect.x = tileX;
		srcRect.y = tileY;
		srcRect.w = srcRect.h = BLOCK_H;

		destRect.x = x = xpos;
		destRect.y = y = ypos;
		destRect.w = destRect.h = BLOCK_H * Game::MAP_SCALE;
	}

	void draw() override
	{
		TextureManager::Draw(texture, &srcRect, &destRect, SDL_FLIP_NONE);
	}

	void update() override
	{
		// tịnh tiến theo camera
		destRect.x = x - Game::camera.x;
		destRect.y = y -Game::camera.y;
	}
};