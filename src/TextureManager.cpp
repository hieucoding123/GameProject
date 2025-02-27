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
