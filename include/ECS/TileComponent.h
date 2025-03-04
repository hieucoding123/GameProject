#pragma once

#include "Components.h"

class TileComponent : public Component
{
private:
	int oldScale;		// tỉ lệ cũ
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

		destRect.x = x = xpos * Game::MAP_SCALE;
		destRect.y = y = ypos * Game::MAP_SCALE;
		destRect.w = destRect.h = BLOCK_H * Game::MAP_SCALE;

		oldScale = Game::MAP_SCALE;
	}

	void draw() override
	{
		TextureManager::Draw(texture, &srcRect, &destRect, SDL_FLIP_NONE);
	}

	void update() override
	{
		// sửa lại x khi tỉ lệ thay đổi
		if (Game::MAP_SCALE != oldScale)
		{
			x = x * Game::MAP_SCALE / oldScale;
			y = y * Game::MAP_SCALE / oldScale;
			oldScale = Game::MAP_SCALE;
		}
		// tịnh tiến theo camera
		destRect.x = x - Game::camera.x;
		destRect.y = y -Game::camera.y;

		destRect.w = destRect.h = BLOCK_H * Game::MAP_SCALE;
	}
};