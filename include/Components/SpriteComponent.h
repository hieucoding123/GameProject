#pragma once
#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent
{
public:
	SpriteComponent();
	SpriteComponent(const char* path, std::unique_ptr<SDL_Rect>& rect);

	void update();
	void draw();

	// srcRect
	SDL_Rect* getSrcRect();

	// đặt tỉ lệ
	void setScale(int s);

	// đặt flip
	void setFlip(SDL_RendererFlip f);

	SDL_RendererFlip getFlip() const;

	int getROL() const;

	SDL_Texture* shareTexture()
	{
		return texture;
	}

	~SpriteComponent();
private:
	std::unique_ptr<SDL_Rect> srcRect;
	SDL_Rect* destRect;
	SDL_Texture* texture;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	int scale;
	int ROL;
};