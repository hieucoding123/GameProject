#include <iostream>

#include "Animation.h"

Animation::Animation(Attribute* attribute, Vector2D* vel,
	SDL_Rect* rect, const std::map<int, std::vector<int>>& FIGURE)
{
	srcRect = rect;
	attrib = attribute;
	velocity = vel;
	figure = FIGURE;

	frames = figure.at(attrib->state)[0];
	speed = figure.at(attrib->state)[1];
	srcRect->x = figure.at(attrib->state)[2];
	srcRect->y = figure.at(attrib->state)[3];
	srcRect->w = figure.at(attrib->state)[4];
	srcRect->h = figure.at(attrib->state)[5];

	currentFrame = 0;
	lastUpdate = SDL_GetTicks();
	animFinished = true;
}

void Animation::setState(int s)
{
	attrib->state = s;
	frames = figure.at(attrib->state)[0];
	speed = figure.at(attrib->state)[1];
	srcRect->x = figure.at(attrib->state)[2];
	srcRect->y = figure.at(attrib->state)[3];
	srcRect->w = figure.at(attrib->state)[4];
	srcRect->h = figure.at(attrib->state)[5]; 

	currentFrame = 0;
	lastUpdate = SDL_GetTicks();
}

void Animation::setFinished(bool b)
{
	animFinished = b;
}

std::vector<int> Animation::getEffectInfor(int state)
{
	return figure.at(state);
}

void Animation::update()
{
	Uint32 now = SDL_GetTicks();
	if (now - lastUpdate > speed) {
		currentFrame++;
		lastUpdate = now;
		srcRect->x += srcRect->w;

		if (currentFrame >= frames) {
			if (attrib->state != (int)SDLK_d)
			{
				this->setState(-1);
				velocity->x = 0;
				velocity->y = 0;
			}
			else
			{
				currentFrame = 0;	// nếu đang chạy -> chạy tiếp
				srcRect->x = figure.at(attrib->state)[2];
			}
			animFinished = true;
			//entity->attrib.isHitting = false;
		}
	}

	srcRect->y = figure.at(attrib->state)[3];
	srcRect->w = figure.at(attrib->state)[4];
	srcRect->h = figure.at(attrib->state)[5];

	//std::cout << srcRect->x;
}

Animation::~Animation()
{

}