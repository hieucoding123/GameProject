#include "Akainu.h"
#include "PlaySection.h"
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
	sprite = std::make_unique<SpriteComponent>(AKAINU_IMG_PATH, rect);
	sprite->getSrcRect()->w = 46;
	sprite->getSrcRect()->h = 80;
	animation = std::make_unique<Animation>(attrib.get(), transform->getVelocity(), sprite->getSrcRect(), AKAINU);
}
void Akainu::update()
{
	GameObject::update();
	// cập nhật vị trí trên màn hình

	if (transform->getYPos() + rect->h >= (GROUND * PlaySection::MAP_SCALE))
	{
		transform->setYpos((GROUND * PlaySection::MAP_SCALE) - rect->h);
	}
	if (transform->getXPos() + rect->w >= (WIDTH * PlaySection::MAP_SCALE))
	{
		transform->setXPos(WIDTH * PlaySection::MAP_SCALE - rect->w);
	}

	animation->update();
	
	PlaySection::effectManager.checkVar(attrib.get(), rect.get());
}
void Akainu::draw()
{
	GameObject::draw();
}

void Akainu::ADWSController()
{
	if (Game::event.type == SDL_KEYDOWN && animation->isFinished())
	{
		int x = transform->getXPos();
		int y = transform->getYPos();
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_d:
			if (animation->setStateSuccess((int)SDLK_d))
			{
				transform->setVx(1);
				animation->setFinished(true);
				sprite->setFlip(SDL_FLIP_NONE);
			}
			break;
		case SDLK_a:
			if (animation->setStateSuccess((int)SDLK_d))
			{
				transform->setVx(-1);
				animation->setFinished(true);
				sprite->setFlip(SDL_FLIP_HORIZONTAL);
			}
			break;
		case SDLK_w:
			if (animation->setStateSuccess((int)SDLK_w))
			{
				transform->setVy(-5);
				animation->setFinished(false);
				Game::playSound(5);
			}
			break;
		case SDLK_r:
			if (animation->setStateSuccess((int)SDLK_r))
			{
				transform->setVx(0);
				animation->setFinished(false);
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-3),
					0, 0, 2, sprite->getFlip(), x + 500 * sprite->getROL(), y));
			}
			break;
		case SDLK_u:
			if (animation->setStateSuccess((int)SDLK_u))
			{
				transform->setVx(0);
				animation->setFinished(false);
			}
			break;
		case SDLK_c:
			if (animation->setStateSuccess((attrib->onGround) ? (int)SDLK_c : (int)SDLK_q))
			{
				transform->setVx(0);
				animation->setFinished(false);
			}
			break;
		case SDLK_f:
			if (animation->setStateSuccess((int)SDLK_f))
			{
				transform->setVx(5 * sprite->getROL());
				animation->setFinished(false);
				Game::playSound(4);
			}
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
		int x = transform->getXPos();
		int y = transform->getYPos();
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			if (animation->setStateSuccess((int)SDLK_d))
			{
				transform->setVx(1);
				animation->setFinished(true);
				sprite->setFlip(SDL_FLIP_NONE);
			}
			break;
		case SDLK_LEFT:
			if (animation->setStateSuccess((int)SDLK_d))
			{
				transform->setVx(-1);
				animation->setFinished(true);
				sprite->setFlip(SDL_FLIP_HORIZONTAL);
			}
			break;
		case SDLK_UP:
			if (animation->setStateSuccess((int)SDLK_w))
			{
				transform->setVy(-5);
				animation->setFinished(false);
				Game::playSound(5);
			}
			break;
		case SDLK_m:
			if (animation->setStateSuccess((int)SDLK_r))
			{
				transform->setVx(0);
				animation->setFinished(false);
				PlaySection::effectManager.addEffect(std::make_unique<Effect>(sprite->shareTexture(), attrib->ID, animation->getEffectInfor(-3),
					0, 0, 2, sprite->getFlip(), x + 500 * sprite->getROL(), y));
			}
			break;
		case SDLK_k:
			if (animation->setStateSuccess((int)SDLK_u))
			{
				transform->setVx(0);
				animation->setFinished(false);
			}
			break;
		case SDLK_l:
			if (animation->setStateSuccess((attrib->onGround) ? (int)SDLK_c : (int)SDLK_q))
			{
				transform->setVx(0);
				animation->setFinished(false);
			}
			break;
		case SDLK_RCTRL:
			if (animation->setStateSuccess((int)SDLK_f))
			{
				transform->setVx(5 * sprite->getROL());
				animation->setFinished(false);
				Game::playSound(4);
			}
			break;
		default:
			break;
		}
	}
}
