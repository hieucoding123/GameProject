#include "TextureManager.h"
#include "Const.h"

SDL_Texture* TextureManager::LoadTexture(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, srcRect, destRect, NULL, NULL, flip);
}

void TextureManager::DrawHP(int x, int y, int w, int hBar, int wBar, const SDL_Color& bgColor, const SDL_Color& color)
{
	SDL_Rect bg = { x, y, wBar, hBar };
	SDL_SetRenderDrawColor(Game::renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderFillRect(Game::renderer, &bg);
	if (w < 0) w = 0;
	if (w > wBar) w = wBar;
	SDL_Rect fillRect = { x, y, w, hBar };
	SDL_SetRenderDrawColor(Game::renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(Game::renderer, &fillRect);
}

void TextureManager::DrawEnergy(int x, int y, int w, int hBar, int wBar, const SDL_Color& bgColor, const SDL_Color& color)
{
	SDL_Rect bg = { x, y, wBar - 20, hBar / 2 };
	SDL_SetRenderDrawColor(Game::renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderFillRect(Game::renderer, &bg);

	if (w < 0) w = 0;
	if (w > HP_W - 20) w = wBar - 20;
	SDL_Rect fillRect = { x, y, w, hBar / 2};
	SDL_SetRenderDrawColor(Game::renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(Game::renderer, &fillRect);
}

void TextureManager::DrawCollisionImage(const SDL_Rect* rect)
{
	SDL_Texture* texture = LoadTexture(collisionImgPath);
	SDL_Rect collisionSrc = { 0, 0, 282, 282 };
	SDL_Rect destRect = { rect->x, rect->y, collisionSrc.w / PlaySection::MAP_SCALE, collisionSrc.h / PlaySection::MAP_SCALE };
	Draw(texture, &collisionSrc, &destRect, SDL_FLIP_NONE);
}
