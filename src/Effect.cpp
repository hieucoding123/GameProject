#include "Effect.h"
#include "Game.h"

Effect::Effect()
{ }

Effect::Effect(const std::vector<int>& v, int vX, int vY, int scl, SDL_RendererFlip f, int xpos, int ypos)
{
	active = true;
	frames = v[0];
	speed = v[1];
	damage = v[7];

	vx = vX*((int)f * -2 + 1);
	vy = vY;

	srcRect = { v[2], v[3], v[4], v[5] };
	destRect = { xpos, ypos, srcRect.w * scl, srcRect.h * scl };

	lastUpdate = SDL_GetTicks();
	currentFrame = 0;
}

void Effect::update()
{
	// cho hi?u ?ng chuy?n ??ng
	Uint32 now = SDL_GetTicks();
	if ((now - lastUpdate) > speed) {
		currentFrame++;
		lastUpdate = now;

		if (currentFrame >= frames) {
			active = false;
			destRect = { 0 };
		}
	}

	srcRect.x = currentFrame * srcRect.w;

	// cho hi?u ?ng di chuy?n
	destRect.x += vx;
	destRect.y += vy;
}