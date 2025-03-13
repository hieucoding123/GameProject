#pragma once

#include "Game.h"

// quản lý và cài texture
class TextureManager
{
public:

	static SDL_Texture* LoadTexture(const char* path);

	static void Draw(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect, SDL_RendererFlip flip);

	static void DrawHP(int x, int y, int w, const SDL_Color& color, const SDL_Color& bgColor);

	static void DrawEnergy(int x, int y, int w, const SDL_Color& color, const SDL_Color& bgColor);
	
	static void DrawCollisionImage(const SDL_Rect* rect);
};