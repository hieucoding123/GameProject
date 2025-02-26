#pragma once

#include "Components.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	TileComponent() = default;
	TileComponent(int tileX, int tileY, int xpos, int ypos)
	{
		texture = TextureManager::LoadTexture(imageTilePath);

		srcRect.x = tileX;
		srcRect.y = tileY;
		srcRect.w = srcRect.h = BLOCK_H;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = BLOCK_H * MAP_SCALE;
	}

	void draw() override
	{
		TextureManager::Draw(texture, &srcRect, &destRect);
	}
};