#include "Effect.h"
#include "Game.h"

Effect::Effect()
{
	effectTexture = nullptr;
}

Effect::Effect(SDL_Texture* texture, int id, const std::vector<int>& v, int vX, int vY,
	int scl, SDL_RendererFlip f, int xpos, int ypos)
{
	effectTexture = texture;
	ID = id;
	effectFlip = f;
	active = true;
	frames = v[0];
	speed = v[1];
	damage = v[7];

	vx = vX*((int)f * -2 + 1);			// tịnh tiến theo hướng
	vy = vY;

	srcRect = { v[2], v[3], v[4], v[5] };
	destRect = { xpos, ypos, srcRect.w * scl, srcRect.h * scl };
	lastUpdate = SDL_GetTicks();
	currentFrame = 0;
}

void Effect::update()
{
	// cho hiệu ứng chuyển động
	Uint32 now = SDL_GetTicks();
	if ((now - lastUpdate) > speed) {
		currentFrame++;
		srcRect.x += srcRect.w;
		lastUpdate = now;

		if (currentFrame >= frames) {
			active = false;
			destRect = { 0 };
		}
	}

	// cho hiệu ứng di chuyển
	destRect.x += vx;
	destRect.y += vy;
}

SDL_Rect Effect::getRect() const
{
	return destRect;
}

int Effect::getDamage() const
{
	return damage;
}

void Effect::setDamage()
{
	damage = 0;
}

int Effect::getID() const
{
	return ID;
}


void Effect::draw()
{
	TextureManager::Draw(effectTexture, &srcRect, &destRect, effectFlip);
}