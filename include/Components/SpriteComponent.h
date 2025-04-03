#pragma once
#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent
{
public:
	SpriteComponent();
	/*
	* @param path đường dẫn đến ảnh
	* @param rect hình chữ nhật chứa đối tượng
	*/
	SpriteComponent(const char* path, std::unique_ptr<SDL_Rect>& rect);

	void update();
	void draw();

	// srcRect
	SDL_Rect* getSrcRect();

	/*
	* Tùy chỉnh tỉ lệ
	* @param s Tỉ lệ
	*/
	void setScale(int s);

	/*
	* Tùy chỉnh lật ảnh
	* @param f Chỉ số quy định lật ảnh trong SDL
	*/
	void setFlip(SDL_RendererFlip f);

	SDL_RendererFlip getFlip() const;

	int getROL() const;

	/*
	* Chia sẻ texture ra ngoài đối tượng
	* @return texture của đối tượng gọi
	*/
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