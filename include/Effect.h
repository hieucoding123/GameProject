#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include <vector>

class Effect
{
public:
	Effect();
	Effect(SDL_Texture* texture, const std::vector<int>& v, int vX, int vY,
		int scl, SDL_RendererFlip f, int xpos, int ypos);
	void update();
	void draw();
	bool isActive() const { return active; }
	SDL_Rect getRect() const;
	int getDamage() const;
	void setDamage();
private:
	SDL_Texture* effectTexture;
	SDL_Rect srcRect, destRect;
	SDL_RendererFlip effectFlip;
	int frames;
	int speed;
	int damage;
	int vx, vy;

	Uint32 lastUpdate;
	bool active = false;
	int currentFrame;
};