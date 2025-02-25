#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}