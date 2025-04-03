#pragma once

#include "Game.h"
#include "PlaySection.h"

// quản lý và cài texture
class TextureManager
{
public:
	/*
	* Tải texture khi có đường dẫn ảnh
	* @param path đường dẫn đến ảnh
	* @return SDL_Texture* trỏ đến texture
	*/
	static SDL_Texture* LoadTexture(const char* path);

	/*
	* Vẽ lên màn hình qua renderer
	* @param texture con trỏ đến texture cần vẽ
	* @param srcRect con trỏ đến hình chữ nhật gốc
	* @param destRect con trỏ đến hình chữ nhật đích
	* @param flip quy định lật ảnh
	*/
	static void Draw(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect, SDL_RendererFlip flip);

	static void DrawHP(int x, int y, int w, int hBar, int wBar, const SDL_Color& color, const SDL_Color& bgColor);

	static void DrawEnergy(int x, int y, int w, int hBar, int wBar, const SDL_Color& color, const SDL_Color& bgColor);
	
	/*
	*Vẽ ảnh khi có va chạm
	* @param rect chứa vị trí cần vẽ
	*/
	static void DrawCollisionImage(const SDL_Rect* rect);
};