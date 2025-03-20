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

bool Animation::setStateSuccess(int s)
{
	if (figure.at(s)[6] <= attrib->energy)
	{
		attrib->state = s;
		// trừ năng lượng
		attrib->energy -= figure.at(s)[6] * 0.5;
		frames = figure.at(s)[0];
		speed = figure.at(s)[1];
		srcRect->x = figure.at(s)[2];
		srcRect->y = figure.at(s)[3];
		srcRect->w = figure.at(s)[4];
		srcRect->h = figure.at(s)[5];
		// Cài đặt sát thương cận chiến
		attrib->damage = figure.at(s)[7];

		currentFrame = 0;
		lastUpdate = SDL_GetTicks();
		return true;
	}
	return false;
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
	// nếu dính sát thương thì sẽ chuyển hoạt hình
	if (attrib->isHitting)
	{
		// Nhận sát thương (không di chuyển, không tiếp nhận điều khiển)
		this->setStateSuccess(-4);
		velocity->x = 0;
		velocity->y = 0;
		attrib->isHitting = false;
		animFinished = false;
	}
	else if (!attrib->onGround && animFinished)
	{
		this->setStateSuccess(-2);
	}
	Uint32 now = SDL_GetTicks();
	if (now - lastUpdate > speed) {
		currentFrame++;
		lastUpdate = now;
		srcRect->x += srcRect->w;

		if (currentFrame >= frames) {
			if (attrib->state != (int)SDLK_d)
			{
				this->setStateSuccess(-1);
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