#pragma once

#include "SDL.h"
#include <vector>

class Effect
{
public:
	Effect();
	Effect(const std::vector<int>& v, int vX, int vY, int scl, SDL_RendererFlip f, int xpos, int ypos);
	void update();
	bool isActive() const { return active; }
	SDL_Rect srcRect, destRect;
private:
	int frames;
	int speed;
	int damage;
	int vx, vy;

	Uint32 lastUpdate;
	bool active = false;
	int currentFrame;
};