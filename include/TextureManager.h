#pragma once

#include "Game.h"

// quản lý và cài texture
class TextureManager
{
public:
	/*
	* Tải texture khi có đường dẫn ảnh
	* @param const char* đường dẫn đến ảnh
	* @return SDL_Texture* trỏ đến texture
	*/
	static SDL_Texture* LoadTexture(const char* path);

	/*
	* Vẽ lên màn hình qua renderer
	* @param SDL_Texture* con trỏ đến texture
	* @param SDL_Rect* con trỏ đến srcRect
	* @param SDL_Rect* con trỏ đến destRect
	* @param SDL_RendererFlip quy định lật ảnh
	*/
	static void Draw(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect, SDL_RendererFlip flip);

	static void DrawHP(int x, int y, int w, const SDL_Color& color, const SDL_Color& bgColor);

	static void DrawEnergy(int x, int y, int w, const SDL_Color& color, const SDL_Color& bgColor);
	
	/*
	*Vẽ ảnh khi có va chạm
	* @param SDL_Rect* chứa vị trí cần vẽ
	*/
	static void DrawCollisionImage(const SDL_Rect* rect);
};