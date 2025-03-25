#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include <vector>

class Effect
{
public:
	Effect();
	Effect(SDL_Texture* texture, int id, const std::vector<int>& v, int vX, int vY,
		int scl, SDL_RendererFlip f, int xpos, int ypos);
	void update();
	void draw();
	bool isActive() const { return active; }
	SDL_Rect getRect() const;
	int getDamage() const;
	/*
	* đặt sát thương về 0
	*/
	void setDamage();
	int getID() const;
private:
	SDL_Texture* effectTexture;
	SDL_Rect srcRect, destRect;
	SDL_RendererFlip effectFlip;
	int frames;
	int speed;
	int damage;
	int vx, vy;
	int realX, realY;

	Uint32 lastUpdate;
	bool active = false;
	int currentFrame;
	int ID;					// ID xác định đối tượng tạo ra hiệu ứng
};