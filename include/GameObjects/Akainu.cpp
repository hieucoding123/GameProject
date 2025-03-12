﻿#include "Akainu.h"
#include "EffectManager.h"

Akainu::Akainu()
{
	GameObject::GameObject();
}

// khởi tạo
void Akainu::init()
{
	GameObject::init();
	transform->setSpeed(3);
	sprite = std::make_unique<SpriteComponent>("D:/CoDE/C++/Tu_hoc_Cpp/Tu_hoc_Cpp/assets/akainu_stand.png", rect);
	sprite->getSrcRect()->w = 46;
	sprite->getSrcRect()->h = 80;
	animation = std::make_unique<Animation>(attrib.get(), transform->getVelocity(), sprite->getSrcRect(), AKAINU);
}
void Akainu::update()
{
	GameObject::update();
	// cập nhật vị trí trên màn hình

	//std::cout << transform->getXPos() << ' ' << transform->getYPos() << std::endl;

	if (transform->getYPos() + rect->h >= (GROUND * Game::MAP_SCALE))
	{
		transform->setYpos((GROUND * Game::MAP_SCALE) - rect->h);
	}
	if (transform->getXPos() + rect->w >= (WIDTH * Game::MAP_SCALE))
	{
		transform->setXPos(WIDTH * Game::MAP_SCALE - rect->w);
	}
	if (this->hasCamera())
	{
		rect->x = transform->getXPos() - Game::camera.x;
		rect->y = transform->getYPos() - Game::camera.y;
	}
	else {
		rect->x = transform->getXPos();
		rect->y = transform->getYPos();
	}

	animation->update();
}
void Akainu::draw()
{
	GameObject::draw();
}

void Akainu::ADWSController()
{
	if (Game::event.type == SDL_KEYDOWN && animation->isFinished())
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_d:
			transform->setVx(1);
			animation->setState((int)SDLK_d);
			animation->setFinished(true);
			sprite->setFlip(SDL_FLIP_NONE);
			break;
		case SDLK_a:
			transform->setVx(-1);
			animation->setState((int)SDLK_d);
			animation->setFinished(true);
			sprite->setFlip(SDL_FLIP_HORIZONTAL);
			break;
		case SDLK_w:
			transform->setVy(-5);
			animation->setState((int)SDLK_w);
			animation->setFinished(false);
			break;
		case SDLK_r:
			transform->setVx(0);
			animation->setState((int)SDLK_r);
			animation->setFinished(false);
			Game::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), animation->getEffectInfor(-3),
				9, 0, 2, sprite->getFlip(), rect->x + rect->w * sprite->getROL(), rect->y));
			break;
		case SDLK_u:
			transform->setVx(0);
			animation->setState((int)SDLK_u);
			animation->setFinished(false);
			break;
		default:
			break;
		}
	}
}

void Akainu::LRUDController()
{
	if (Game::event.type == SDL_KEYDOWN && animation->isFinished())
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			transform->setVx(1);
			animation->setState((int)SDLK_d);
			animation->setFinished(true);
			sprite->setFlip(SDL_FLIP_NONE);
			break;
		case SDLK_LEFT:
			transform->setVx(-1);
			animation->setState((int)SDLK_d);
			animation->setFinished(true);
			sprite->setFlip(SDL_FLIP_HORIZONTAL);
			break;
		case SDLK_UP:
			transform->setVy(-5);
			animation->setState((int)SDLK_w);
			animation->setFinished(false);
			break;
		case SDLK_m:
			transform->setVx(0);
			animation->setState((int)SDLK_r);
			animation->setFinished(false);
			Game::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), animation->getEffectInfor(-3),
				0, 0, 2, sprite->getFlip(), rect->x + rect->w * sprite->getROL(), rect->y));
			break;
		case SDLK_k:
			transform->setVx(0);
			animation->setState((int)SDLK_u);
			animation->setFinished(false);
			break;
		default:
			break;
		}
	}
}

void Akainu::setPosition(int xpos, int ypos)
{
	transform->setXPos(xpos);
	transform->setYpos(ypos);
}

int	Akainu::getHP() const
{
	return attrib->hp;
}
int	Akainu::getEnergy() const
{
	return attrib->energy;
}
